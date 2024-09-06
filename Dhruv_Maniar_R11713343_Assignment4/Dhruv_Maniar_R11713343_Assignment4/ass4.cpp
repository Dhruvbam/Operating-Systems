/*=============================================================================
Title       : ass4.cpp
Description : A program that demonstrates multithreading in C++ using producer-consumer problem
Author      : Dhruv Maniar R11713343
Date        : 3/20/2024
Version     : 1.0
Usage       : Compile and run this program using a C++ compiler
Notes       : This program uses atomic variables, semaphores, and condition variables
=============================================================================*/

// libraries
#include <iostream>
#include <thread>
#include <semaphore.h>
#include <queue>
#include <fstream>
#include <cmath>
#include <atomic>

using namespace std;

// Global variables
atomic<bool> done(false);
ofstream evenfile("even.out");
ofstream oddfile("odd.out");
ofstream positivefile("positive.out");
ofstream negativefile("negative.out");
ofstream squarefile("square.out");
ofstream cubefile("cube.out");
int integer;
int buffer_size = 40000;
queue<int> buffer;
sem_t sem_producer;
sem_t sem_consumer;
sem_t sem_writer;
vector<int> evenout;
vector<int> oddout;
vector<int> positiveout;
vector<int> negativeout;
vector<int> cubeout;
vector<int> squareout;

/*-------------------------------------------------------------------------------
  FunctionName: producer
  Purpose: Reads data from input file and stores it in the buffer queue
  Type: void 
  Parameters: inputFile - name of the input file
  -------------------------------------------------------------------------------*/
void producer(string inputFile) {
    ifstream file(inputFile);
    if (!file) {
        cerr << "Error: Failed to open file " << inputFile << endl;
        done.store(true);
        sem_post(&sem_producer);
        return;
    }
    while (file >> integer) {
        sem_wait(&sem_producer);
        if (done.load()) {
            sem_post(&sem_consumer);
            return;
        }
        buffer.push(integer);
        sem_post(&sem_consumer);
    }
    done.store(true);
    sem_post(&sem_consumer);
}

/*-------------------------------------------------------------------------------
  FunctionName: cube_checker
  Purpose: Checks if a number is a perfect cube and adds it to the cube output buffer
  Type: void
  Parameters: item - the number to be checked
  -------------------------------------------------------------------------------*/
void cube_checker(int item) {
    int cube_root = round(cbrt(item));
    if (cube_root * cube_root * cube_root == item) {
        cubeout.push_back(item);
    }
}

/*-------------------------------------------------------------------------------
  FunctionName: square_checker
  Purpose: Checks if a number is a perfect square and adds it to the square output buffer
  Type: void
  Parameters: item - the number to be checked
  -------------------------------------------------------------------------------*/
void square_checker(int item) {
    int root = sqrt(abs(item));
    if (root * root == abs(item)) {
        squareout.push_back(item);
    }
}

/*-------------------------------------------------------------------------------
  FunctionName: consumer
  Purpose: Consumes data from the buffer and processes it, storing the results in output buffers
  Type: void
  Parameters: None
  -------------------------------------------------------------------------------*/
void consumer() {
    while (true) {
        sem_wait(&sem_consumer);
        if (buffer.empty() && done.load()) {
            sem_post(&sem_writer);
            return;
        }
        int item = buffer.front();
        buffer.pop();
        sem_post(&sem_producer);
        cube_checker(item);
        if (item % 2 == 0) {
            evenout.push_back(item);
        } else {
            oddout.push_back(item);
        }
        if (item >= 0) {
            square_checker(item);
        }
        if (item > 0) {
            positiveout.push_back(item);
        } else if (item < 0) {
            negativeout.push_back(item);
        }
    }
}

/*-------------------------------------------------------------------------------
  FunctionName: writer
  Purpose: Writes the contents of the output buffers to respective output files
  Type: void
  Parameters: None
  -------------------------------------------------------------------------------*/
void writer() {
    sem_wait(&sem_writer);
    for (size_t i = 0; i < evenout.size(); i++) {
        evenfile << evenout[i] << endl;
    }
    for (size_t i = 0; i < oddout.size(); i++) {
        oddfile << oddout[i] << endl;
    }
    for (size_t i = 0; i < positiveout.size(); i++) {
        positivefile << positiveout[i] << endl;
    }
    for (size_t i = 0; i < negativeout.size(); i++) {
        negativefile << negativeout[i] << endl;
    }
    for (size_t i = 0; i < cubeout.size(); i++) {
        cubefile << cubeout[i] << endl;
    }
    for (size_t i = 0; i < squareout.size(); i++) {
        squarefile << squareout[i] << endl;
    }
}

/*-------------------------------------------------------------------------------
  FunctionName: main
  Purpose: Entry point of the program
  Type: int
  Parameters: argc - number of command-line arguments, argv - array of command-line arguments
  -------------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {

    sem_init(&sem_producer, 0, 1);
    sem_init(&sem_consumer, 0, 0);
    sem_init(&sem_writer, 0, 0);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    thread prod(producer, argv[1]);
    thread cons(consumer);
    thread write(writer);

    prod.join();
    cons.join();
    write.join();

    evenfile.close();
    oddfile.close();
    positivefile.close();
    negativefile.close();
    cubefile.close();
    squarefile.close();

    sem_destroy(&sem_producer);
    sem_destroy(&sem_consumer);
    sem_destroy(&sem_writer);

    return 0;
}