/*
=============================================================================
Title       : ass5.cpp
Description : Program to simulate various process scheduling algorithms.
Author      : Dhruv Maniar
Date        : 4/6/24 
Version     : 1.0
Usage       : Compile and run this program using a C++ compiler.
Notes       : This program requires a plain text input file with process information.
C++ Version : C++98
=============================================================================
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

// Structure to hold process information
struct Process {
    int id;             // Unique identifier for the process
    string name;        // Name of the process
    int arrivalTime;    // Time at which the process arrives
    int serviceTime;    // Time required for the process to complete
};

// Output file names
const string FCFS_OUTPUT = "fcfs.out";
const string RR_10_OUTPUT = "rr_10.out";
const string RR_40_OUTPUT = "rr_40.out";
const string SPN_OUTPUT = "spn.out";
const string SRT_OUTPUT = "srt.out";
const string HRRN_OUTPUT = "hrrn.out";
const string FEEDBACK_OUTPUT = "feedback.out";

// Function declarations
void ReadInput(const string& filename, vector<Process>& processList);
void WriteOutput(const string& filename, const string& data);
void FirstComeFirstServe(const vector<Process>& processList);
void RoundRobinScheduling(const vector<Process>& processList, int timeQuantum);
void ShortestProcessNext(const vector<Process>& processList);
void ShortestRemainingTime(const vector<Process>& processList);
double ResponseRatio(int arrivalTime, int serviceTime, int currentTime);
void HighestResponseRatioNext(const vector<Process>& processList);
void Feedback(const vector<Process>& processList, int timeQuantum);

// Main function - Entry point of the program
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please provide the input file name." << endl;
        return 1;
    }

    string inputFile = argv[1];
    vector<Process> processList;
    ReadInput(inputFile, processList);

    FirstComeFirstServe(processList);
    RoundRobinScheduling(processList, 10);
    RoundRobinScheduling(processList, 40);
    ShortestProcessNext(processList);
    ShortestRemainingTime(processList);
    HighestResponseRatioNext(processList);
    Feedback(processList, 10);

    return 0;
}

// Function to read input from file
void ReadInput(const string& filename, vector<Process>& processList) {
    ifstream fileStream(filename.c_str());
    if (!fileStream) {
        cerr << "Error: File not found: " << filename << endl;
        return;
    }

    string line;
    int index = 0;
    while (getline(fileStream, line)) {
        istringstream lineStream(line);
        string name, arrivalTimeStr, serviceTimeStr;
        lineStream >> name >> arrivalTimeStr >> serviceTimeStr;

        Process process;
        process.id = index++;
        process.name = name;

        istringstream arrivalStream(arrivalTimeStr);
        int arrivalTime;
        arrivalStream >> arrivalTime;
        process.arrivalTime = arrivalTime;

        istringstream serviceStream(serviceTimeStr);
        int serviceTime;
        serviceStream >> serviceTime;
        process.serviceTime = serviceTime;

        processList.push_back(process);
    }

    fileStream.close();
}

// Function to write output to file
void WriteOutput(const string& filename, const string& data) {
    ofstream fileStream(filename.c_str());
    if (!fileStream) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return;
    }

    fileStream << data;
    fileStream.close();
    cout << "File " << filename << " written successfully!" << endl << endl;
}

// Function for First Come First Serve Scheduling
void FirstComeFirstServe(const vector<Process>& processList) {
    string output;
    int currentTime = 0;
    int timeElapsed = 0;

    cout << "First Come First Serve Scheduling:" << endl;

    for (vector<Process>::const_iterator it = processList.begin(); it != processList.end(); ++it) {
        const Process& process = *it;
        timeElapsed = 0;
        while (timeElapsed < process.serviceTime) {
            output += process.name + "\n";
            cout << currentTime << "ms: Process " << process.name << endl;
            timeElapsed += 10;
            currentTime += 10;
        }

        if (it != processList.end() - 1) {
            vector<Process>::const_iterator next_it = it + 1;
            int nextArrivalTime = next_it->arrivalTime;
            while (currentTime < nextArrivalTime) {
                output += "None\n";
                cout << "No process" << endl;
                currentTime += 10;
            }
        }
    }

    WriteOutput(FCFS_OUTPUT, output);
}

// Function for Round Robin Scheduling
void RoundRobinScheduling(const vector<Process>& processList, int timeQuantum) {
    string output;
    queue<Process> readyQueue;
    vector<int> remainingServiceTime(processList.size());
    int currentTime = 0;
    int index = 1;

    for (vector<Process>::const_iterator it = processList.begin(); it != processList.end(); ++it) {
        const Process& process = *it;
        remainingServiceTime[process.id] = process.serviceTime;
    }

    readyQueue.push(processList[0]);

    cout << "Round Robin Scheduling (Time Quantum = " << timeQuantum << "):" << endl;

    while (!readyQueue.empty() || index < processList.size()) {
        if (readyQueue.empty()) {
            readyQueue.push(processList[index]);
            currentTime = processList[index].arrivalTime;
            index++;
        }

        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int timeToExecute = min(timeQuantum, remainingServiceTime[currentProcess.id]);

        for (int i = 0; i < timeToExecute; i += 10) {
            output += currentProcess.name + "\n";
            cout << currentTime << "ms: Process " << currentProcess.name << endl;
            currentTime += 10;

            while (index < processList.size() && processList[index].arrivalTime <= currentTime) {
                readyQueue.push(processList[index]);
                index++;
            }
        }

        remainingServiceTime[currentProcess.id] -= timeToExecute;

        if (remainingServiceTime[currentProcess.id] > 0) {
            readyQueue.push(currentProcess);
        }
    }

    string filename = timeQuantum == 10 ? RR_10_OUTPUT : RR_40_OUTPUT;
    WriteOutput(filename, output);
}

// Function for Shortest Process Next Scheduling
void ShortestProcessNext(const vector<Process>& processList) {
    string output;
    vector<int> remainingServiceTime(processList.size());
    vector<bool> isCompleted(processList.size(), false);
    int currentTime = 0;
    int processesCompleted = 0;

    for (vector<Process>::const_iterator it = processList.begin(); it != processList.end(); ++it) {
        const Process& process = *it;
        remainingServiceTime[process.id] = process.serviceTime;
    }

    cout << "Shortest Process Next Scheduling:" << endl;

    while (processesCompleted < processList.size()) {
        int shortestProcessIndex = -1;
        int shortestServiceTime = numeric_limits<int>::max();

        for (int i = 0; i < processList.size(); ++i) {
            const Process& process = processList[i];
            if (!isCompleted[i] && process.arrivalTime <= currentTime && remainingServiceTime[i] < shortestServiceTime) {
                shortestServiceTime = remainingServiceTime[i];
                shortestProcessIndex = i;
            }
        }

        if (shortestProcessIndex == -1) {
            currentTime += 10;
            continue;
        }

        output += processList[shortestProcessIndex].name + "\n";
        cout << currentTime << "ms: Process " << processList[shortestProcessIndex].name << endl;
        remainingServiceTime[shortestProcessIndex] -= 10;
        currentTime += 10;

        if (remainingServiceTime[shortestProcessIndex] == 0) {
            processesCompleted++;
            isCompleted[shortestProcessIndex] = true;
        }
    }

    WriteOutput(SPN_OUTPUT, output);
}

// Function for Shortest Remaining Time Scheduling
void ShortestRemainingTime(const vector<Process>& processList) {
    string output;
    vector<int> remainingServiceTime(processList.size());
    vector<bool> isCompleted(processList.size(), false);
    int currentTime = 0;
    int processesCompleted = 0;

    for (vector<Process>::const_iterator it = processList.begin(); it != processList.end(); ++it) {
        const Process& process = *it;
        remainingServiceTime[process.id] = process.serviceTime;
    }

    cout << "Shortest Remaining Time Scheduling:" << endl;

    while (processesCompleted < processList.size()) {
        int shortestProcessIndex = -1;
        int shortestRemainingTime = numeric_limits<int>::max();

        for (int i = 0; i < processList.size(); ++i) {
            const Process& process = processList[i];
            if (!isCompleted[i] && process.arrivalTime <= currentTime && remainingServiceTime[i] < shortestRemainingTime) {
                shortestRemainingTime = remainingServiceTime[i];
                shortestProcessIndex = i;
            }
        }

        if (shortestProcessIndex == -1) {
            currentTime += 10;
            continue;
        }

        output += processList[shortestProcessIndex].name + "\n";
        cout << currentTime << "ms: Process " << processList[shortestProcessIndex].name << endl;
        remainingServiceTime[shortestProcessIndex] -= 10;
        currentTime += 10;

        if (remainingServiceTime[shortestProcessIndex] == 0) {
            processesCompleted++;
            isCompleted[shortestProcessIndex] = true;
        }
    }

    WriteOutput(SRT_OUTPUT, output);
}

double ResponseRatio(int arrivalTime, int serviceTime, int currentTime) {
    return static_cast<double>(currentTime - arrivalTime + serviceTime) / serviceTime;
}

// Function for Highest Response Ratio Next Scheduling
void HighestResponseRatioNext(const vector<Process>& processList) {
    string output;
    vector<int> remainingServiceTime(processList.size());
    vector<bool> isCompleted(processList.size(), false);
    int currentTime = 0;
    int processesCompleted = 0;

    for (vector<Process>::const_iterator it = processList.begin(); it != processList.end(); ++it) {
        const Process& process = *it;
        remainingServiceTime[process.id] = process.serviceTime;
    }

    cout << "Highest Response Ratio Next Scheduling:" << endl;

    while (processesCompleted < processList.size()) {
        int highestRatioIndex = -1;
        double highestRatio = -numeric_limits<double>::max();

        for (int i = 0; i < processList.size(); ++i) {
            const Process& process = processList[i];
            if (!isCompleted[i] && process.arrivalTime <= currentTime) {
                double ratio = ResponseRatio(process.arrivalTime, remainingServiceTime[i], currentTime);
                if (ratio > highestRatio) {
                    highestRatio = ratio;
                    highestRatioIndex = i;
                }
            }
        }

        if (highestRatioIndex == -1) {
            currentTime += 10;
            continue;
        }

        output += processList[highestRatioIndex].name + "\n";
        cout << currentTime << "ms: Process " << processList[highestRatioIndex].name << endl;
        remainingServiceTime[highestRatioIndex] -= 10;
        currentTime += 10;

        if (remainingServiceTime[highestRatioIndex] == 0) {
            processesCompleted++;
            isCompleted[highestRatioIndex] = true;
        }
    }

    WriteOutput(HRRN_OUTPUT, output);
}

// Function for Feedback Scheduling
void Feedback(const vector<Process>& processList, int timeQuantum) {
    string output;
    vector<bool> isCompleted(processList.size(), false);
    vector<int> remainingServiceTime(processList.size());
    vector<int> processPriority(processList.size(), 0);
    vector<queue<int> > readyQueues(4);

    int currentTime = 0;
    int lastProcessTime = 0;

    for (vector<Process>::const_iterator it = processList.begin(); it != processList.end(); ++it) {
        const Process& process = *it;
        remainingServiceTime[process.id] = process.serviceTime;
    }

    for (int i = 0; i < processList.size(); ++i) {
        const Process& process = processList[i];
        if (process.arrivalTime == 0) {
            readyQueues[0].push(i);
        }
    }

    cout << "Feedback Scheduling (Time Quantum = " << timeQuantum << "):" << endl;

    while (true) {
        int currentProcessIndex = -1;

        for (int i = 0; i < 4; ++i) {
            if (!readyQueues[i].empty()) {
                currentProcessIndex = readyQueues[i].front();
                readyQueues[i].pop();
                break;
            }
        }

        if (currentProcessIndex == -1) break;

        int timeToExecute = min(remainingServiceTime[currentProcessIndex], timeQuantum);

        for (int i = 0; i < timeToExecute; i += 10) {
            output += processList[currentProcessIndex].name + "\n";
            cout << currentTime << "ms: Process " << processList[currentProcessIndex].name << endl;
            currentTime += 10;
        }

        remainingServiceTime[currentProcessIndex] -= timeToExecute;

        if (remainingServiceTime[currentProcessIndex] == 0) {
            isCompleted[currentProcessIndex] = true;
        } else {
            processPriority[currentProcessIndex] = min(processPriority[currentProcessIndex] + 1, 3);
            readyQueues[processPriority[currentProcessIndex]].push(currentProcessIndex);
        }

        for (int i = 0; i < processList.size(); ++i) {
            const Process& process = processList[i];
            if (!isCompleted[i] && process.arrivalTime > lastProcessTime && process.arrivalTime <= currentTime) {
                readyQueues[0].push(i);
            }
        }

        lastProcessTime = currentTime;
    }

    WriteOutput(FEEDBACK_OUTPUT, output);
}