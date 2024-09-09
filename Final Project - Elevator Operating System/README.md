# Operating Systems
![Image](https://github.com/Dhruvbam/Operating-Systems/blob/main/Images/ss.jpg)

## About
This repository contains four assignment projects and one final project completed as part of the Operating Systems (CS 4352) course at Texas Tech University. The assignments cover operating system concepts such as Bash scripting, API communication, multithreading, process scheduling, and system synchronization. The final project involves creating a scheduler for an elevator operating system, providing a comprehensive understanding of key OS principles.

## Assignments Overview

1. **Assignment 2: Bash, Makefiles, and Utilizing the HPCC**
   - **Topic:** Bash Scripting and Makefiles
   - **Description:** This assignment involves creating a Bash script for automating tasks such as file decryption and transformation on the HPCC, utilizing GNU 5.4.0.

2. **Assignment 3: Using APIs to Communicate**
   - **Topic:** API Communication
   - **Description:** A C/C++ program that interacts with APIs running in a singularity container. The program sends and retrieves data using PUT and GET requests to modify internal data objects.

3. **Assignment 4: Multithreading**
   - **Topic:** Multithreading and Mutex/Semaphores
   - **Description:** A program that reads integers from a file and processes them concurrently using multiple threads, implementing mutexes or semaphores to ensure thread safety.

4. **Assignment 5: Scheduling**
   - **Topic:** Process Scheduling
   - **Description:** This assignment simulates various process scheduling algorithms, including FCFS, Round Robin, SPN, SRT, and HRRN, based on process data provided through input files.

5. **Final Project: Elevator Operating System**
   - **Topic:** Multithreading and API Communication
   - **Description:** The final project involves developing a multithreaded scheduler for an Elevator OS that communicates with a Python-based system via asynchronous API calls, simulating real-time elevator operations.

## Built With
This repository primarily utilizes:
- <a href="https://www.gnu.org/software/bash/" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" width="36" height="36" alt="Bash" /></a> **Bash**: For scripting and job submission on the HPCC.
- <a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" width="36" height="36" alt="C Programming" /></a> **C/C++**: Used for API communication, multithreading, and scheduling algorithms.

## How to Use
1. Clone the repository:
    ```bash
    git clone https://github.com/your-repo/operating-systems.git
    ```
2. Navigate to the folder for the specific assignment.
3. Compile and run the code using `make`:
    ```bash
    make
    ./assignment_2.sh
    ```

## Learning Outcomes
By completing these assignments and the final project, I gained practical experience in key areas of operating system design:

- **Bash Scripting & Automation**: Developed skills in creating and debugging **Bash scripts** to automate tasks on distributed systems, managing jobs, files, and processes efficiently.
- **API Communication**: Mastered sending and receiving data via **APIs** using C/C++, with a solid understanding of HTTP requests and inter-process communication.
- **Multithreading & Synchronization**: Built multithreaded applications using synchronization techniques like **mutexes** and **semaphores** to ensure thread safety and prevent race conditions.
- **Process Scheduling**: Implemented and analyzed scheduling algorithms, including **FCFS**, **Round Robin**, **SPN**, and **HRRN**, assessing their efficiency and impact on CPU utilization.
- **Systems-Level Problem Solving**: Applied operating system concepts like scheduling and resource allocation, culminating in the **Elevator OS project** with real-world multithreading and API communication challenges.

This experience deepened my understanding of operating system fundamentals and real-world problem-solving.


