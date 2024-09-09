# Operating Systems - Assignment 5: Scheduling
![Image](https://github.com/Dhruvbam/Operating-Systems/blob/main/Images/ass5.jpg)

## About
This project is part of the **Operating Systems (CS 4352)** course at Texas Tech University. The assignment focuses on simulating the scheduling of processes using various **CPU scheduling algorithms**. The program processes input from a file containing process data and simulates the execution of each process based on different scheduling policies.

## Problem Statement
The task involves writing a C/C++ program that simulates the scheduling of processes using the following algorithms:
- **First Come First Serve (FCFS)**
- **Round Robin (RR)** with quantum values of 10ms and 40ms
- **Shortest Process Next (SPN)**
- **Shortest Remaining Time (SRT)**
- **Highest Response Ratio Next (HRRN)**
- **Feedback (quantum = 10ms)**

The input file contains process data, and the program must simulate these algorithms, producing output files indicating which process is running at each 10ms interval.

## Assignment Overview

1. **Assignment 5: Scheduling**
   - **Topic:** Process Scheduling Algorithms
   - **Description:** This assignment requires the implementation of several scheduling algorithms, simulating the scheduling of processes and generating an output file for each algorithm. Each output file will list the process running during each 10ms interval.

## Project Structure
- **ass5.cpp**: The main C++ program that implements the scheduling algorithms and simulates process execution.
- **Makefile**: The Makefile used to compile the source code into an executable named `assignment_5`.
- **CS4352 - Assignment 5.pdf**: The detailed assignment instructions.

## Input/Output
### Input File Specification
- A plain text file where each line contains the following fields separated by tabs:
  - **Process Identifier**: An alphanumeric string.
  - **Arrival Time**: The time (in ms) when the process arrives.
  - **Service Time**: A positive integer representing the time the process requires to complete.

Example Input: P1 0 20 P2 10 50 P3 30 10 P4 50 30

### Output Files
The program will generate separate output files for each scheduling algorithm:
1. **fcfs.out**: First Come First Serve
2. **rr_10.out**: Round Robin (quantum = 10ms)
3. **rr_40.out**: Round Robin (quantum = 40ms)
4. **spn.out**: Shortest Process Next
5. **srt.out**: Shortest Remaining Time
6. **hrrn.out**: Highest Response Ratio Next
7. **feedback.out**: Feedback (quantum = 10ms)

Each line in the output files represents a 10ms interval, listing the process identifier that was running during that time.

Example `fcfs.out`: P1 P1 P2 P2 P3 P4 P4


## Built With
This assignment utilizes:
- <a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" width="36" height="36" alt="C Programming" /></a> **C/C++**: The core programming languages used to implement the scheduling algorithms.
- **Makefiles**: Used to compile the C++ program into an executable on the HPCC.

## How to Use
1. Clone the repository:
    ```bash
    git clone https://github.com/your-repo/operating-systems.git
    cd assignment_5
    ```
2. Compile the program using the Makefile:
    ```bash
    make
    ```
3. Run the program with the input file:
    ```bash
    ./assignment_5 process_data.txt
    ```

## Learning Outcomes
By completing this assignment, I gained hands-on experience in:

- **Scheduling Algorithms**: Implemented multiple CPU scheduling algorithms, including **FCFS**, **Round Robin**, **SPN**, **SRT**, **HRRN**, and **Feedback**, gaining an understanding of their real-world applications and performance.
- **Process Simulation**: Developed the ability to simulate process scheduling, processing data from input files, and analyzing the results across multiple scheduling policies.
- **File Handling**: Enhanced my skills in managing input and output files, ensuring that the program produces accurate outputs for each 10ms time interval.
- **Optimization & Efficiency**: Focused on optimizing scheduling to meet specific time constraints and ensuring that the program runs efficiently on high-performance computing systems.

These experiences helped solidify my understanding of operating system scheduling and resource management.

