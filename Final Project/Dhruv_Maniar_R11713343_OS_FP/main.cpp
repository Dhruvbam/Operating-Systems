/*=============================================================================
Title: scheduler_os.cpp
Description: Elevator Operating System Scheduler
Author: Dhruv Maniar
Date: 4/29/2024
Version: 1.0
Usage: Compile and run this program using the GNU C++ compiler
C++ Version: C++11 or later
=============================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>

using namespace std;

// Struct to represent an elevator
struct Elevator {
    string bay;
    int lowestFloor;
    int highestFloor;
    int currentFloor;
    int capacity;
    vector<int> peopleInside;
};

// Struct to represent a person
struct Person {
    string name;
    int startFloor;
    int endFloor;
    int startTime;
    string assignedBay;
};

// Global variables
unordered_map<string, Elevator> elevatorMap;
unordered_map<string, Person> peopleMap;
queue<string> peopleQueue;
vector<string> peopleWaitingForElevator;
vector<string> peopleInElevators;
vector<string> peopleCompleted;
mutex mtx;
condition_variable cv;
bool simulationStarted = false;

/*=============================================================================
Function: readBuildingFile
Description: Read the building configuration file and populate the elevator map.
Args:
    filename (const string&): The name of the building configuration file.
Returns:
    void
=============================================================================*/
void readBuildingFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string bay, lowestFloorStr, highestFloorStr, currentFloorStr, capacityStr;
            if (getline(iss, bay, '\t') && getline(iss, lowestFloorStr, '\t') &&
                getline(iss, highestFloorStr, '\t') && getline(iss, currentFloorStr, '\t') &&
                getline(iss, capacityStr, '\t')) {
                Elevator elevator;
                elevator.bay = bay;
                elevator.lowestFloor = stoi(lowestFloorStr);
                elevator.highestFloor = stoi(highestFloorStr);
                elevator.currentFloor = stoi(currentFloorStr);
                elevator.capacity = stoi(capacityStr);
                elevatorMap[bay] = elevator;
            }
        }
        file.close();
    } else {
        cerr << "Unable to open the building file." << endl;
    }
}

/*=============================================================================
Function: readPeopleFile
Description: Read the people file and populate the people map.
Args:
    filename (const string&): The name of the people file.
Returns:
    void
=============================================================================*/
void readPeopleFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, startFloorStr, endFloorStr, startTimeStr;
            if (getline(iss, name, '\t') && getline(iss, startFloorStr, '\t') &&
                getline(iss, endFloorStr, '\t') && getline(iss, startTimeStr, '\t')) {
                Person person;
                person.name = name;
                person.startFloor = stoi(startFloorStr);
                person.endFloor = stoi(endFloorStr);
                person.startTime = stoi(startTimeStr);
                peopleMap[name] = person;
            }
        }
        file.close();
    } else {
        cerr << "Unable to open the people file." << endl;
    }
}

/*=============================================================================
Function: movePeopleToQueue
Description: Move people from the people map to the people queue based on their start time.
Args:
    currentTime (int): The current simulation time.
Returns:
    void
=============================================================================*/
void movePeopleToQueue(int currentTime) {
    for (const auto& person : peopleMap) {
        if (person.second.startTime == currentTime) {
            peopleQueue.push(person.first);
        }
    }
}

/*=============================================================================
Function: assignPeopleToElevators
Description: Assign people from the people queue to elevators based on availability.
Args:
    None
Returns:
    void
=============================================================================*/
void assignPeopleToElevators() {
    while (!peopleQueue.empty()) {
        string personName = peopleQueue.front();
        peopleQueue.pop();

        Person& person = peopleMap[personName];
        bool assigned = false;

        // Find the best elevator to assign the person
        for (auto& elevator : elevatorMap) {
            if (elevator.second.currentFloor == person.startFloor &&
                elevator.second.peopleInside.size() < elevator.second.capacity) {
                elevator.second.peopleInside.push_back(person.endFloor);
                person.assignedBay = elevator.first;
                peopleInElevators.push_back(personName);
                assigned = true;
                break;
            }
        }

        if (!assigned) {
            peopleWaitingForElevator.push_back(personName);
        }
    }
}

/*=============================================================================
Function: handleElevatorMovements
Description: Handle elevator movements and remove people from elevators when they reach their destination floor.
Args:
    currentTime (int): The current simulation time.
Returns:
    void
=============================================================================*/
void handleElevatorMovements(int currentTime) {
    for (auto& elevator : elevatorMap) {
        if (!elevator.second.peopleInside.empty()) {
            vector<int> peopleToRemove;
            for (int floor : elevator.second.peopleInside) {
                if (floor == elevator.second.currentFloor) {
                    peopleToRemove.push_back(floor);
                    string personName = peopleInElevators.front();
                    peopleInElevators.erase(peopleInElevators.begin());
                    Person& person = peopleMap[personName];
                    person.assignedBay = "";
                    peopleCompleted.push_back(personName);
                }
            }
            for (int floor : peopleToRemove) {
                elevator.second.peopleInside.erase(
                    remove(elevator.second.peopleInside.begin(), elevator.second.peopleInside.end(), floor),
                    elevator.second.peopleInside.end());
            }

            // Move the elevator to the next floor
            if (!elevator.second.peopleInside.empty()) {
                int nextFloor = elevator.second.peopleInside.front();
                if (nextFloor > elevator.second.currentFloor) {
                    elevator.second.currentFloor++;
                } else {
                    elevator.second.currentFloor--;
                }
            }
        }
    }
}

/*=============================================================================
Function: inputCommunicationThread
Description: The input communication thread function. Communicates with the /NextInput API.
Args:
    None
Returns:
    void
=============================================================================*/
void inputCommunicationThread() {
    while (true) {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [] { return simulationStarted; });

        int currentTime = 0;
        while (currentTime < 18000) {
            movePeopleToQueue(currentTime);
            currentTime++;
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        break;
    }
}

/*=============================================================================
Function: outputCommunicationThread
Description: The output communication thread function. Communicates with the /AddPersonToElevator API.
Args:
    None
Returns:
    void
=============================================================================*/
void outputCommunicationThread() {
    while (true) {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [] { return simulationStarted; });

        int currentTime = 0;
        while (currentTime < 18000) {
            assignPeopleToElevators();
            handleElevatorMovements(currentTime);
            currentTime++;
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        break;
    }
}

/*=============================================================================
Function: schedulerComputationThread
Description: The scheduler computation thread function. Implements the scheduling algorithm.
Args:
    None
Returns:
    void
=============================================================================*/
void schedulerComputationThread() {
    while (true) {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [] { return simulationStarted; });

        int currentTime = 0;
        while (currentTime < 18000) {


            // Sort the people in the queue based on their start time
            vector<string> sortedPeopleQueue(peopleQueue.begin(), peopleQueue.end());
            sort(sortedPeopleQueue.begin(), sortedPeopleQueue.end(), [&](const string& a, const string& b) {
                return peopleMap[a].startTime < peopleMap[b].startTime;
            });

            // Assign people to the nearest available elevator
            for (const string& personName : sortedPeopleQueue) {
                Person& person = peopleMap[personName];
                bool assigned = false;

                // Find the nearest elevator to the person's start floor
                string nearestElevator;
                int minDistance = INT_MAX;
                for (const auto& elevator : elevatorMap) {
                    int distance = abs(elevator.second.currentFloor - person.startFloor);
                    if (distance < minDistance && elevator.second.peopleInside.size() < elevator.second.capacity) {
                        minDistance = distance;
                        nearestElevator = elevator.first;
                    }
                }

                // Assign the person to the nearest elevator
                if (!nearestElevator.empty()) {
                    Elevator& elevator = elevatorMap[nearestElevator];
                    elevator.peopleInside.push_back(person.endFloor);
                    person.assignedBay = nearestElevator;
                    peopleInElevators.push_back(personName);
                    assigned = true;
                }

                // If no elevator is available, add the person to the waiting list
                if (!assigned) {
                    peopleWaitingForElevator.push_back(personName);
                }
            }

            // Clear the people queue after assigning them
            while (!peopleQueue.empty()) {
                peopleQueue.pop();
            }

            currentTime++;
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        break;
    }
}

/*=============================================================================
Function: main
Description: Entry point of the program.
Args:
    argc (int): Number of command-line arguments.
    argv (char*[]): Array of command-line arguments.
Returns:
    int: The exit status of the program.
=============================================================================*/
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <building_file>" << endl;
        return 1;
    }

    // Read building configuration file and people file
    string buildingFile(argv[1]);
    readBuildingFile(buildingFile);
    readPeopleFile("file.ppl");

    // Create and start threads for input communication, output communication, and scheduler computation
    thread inputThread(inputCommunicationThread);
    thread outputThread(outputCommunicationThread);
    thread schedulerThread(schedulerComputationThread);

    // Notify all threads that simulation has started
    {
        lock_guard<mutex> lck(mtx);
        simulationStarted = true;
    }
    cv.notify_all();

    // Join all threads
    inputThread.join();
    outputThread.join();
    schedulerThread.join();

    // Print the final results
    cout << "People Completed Their Journey:" << endl;
    for (const string& person : peopleCompleted) {
        cout << person << endl;
    }

    cout << "People Waiting for Elevator:" << endl;
    for (const string& person : peopleWaitingForElevator) {
        cout << person << endl;
    }

    cout << "People in Elevators:" << endl;
    for (const string& person : peopleInElevators) {
        cout << person << endl;
    }

    return 0;
}
