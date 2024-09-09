# Operating Systems - Assignment 4: Multithreading
![Image](https://github.com/Dhruvbam/Operating-Systems/blob/main/Images/ass4.gif)

## About
This project is part of the **Operating Systems (CS 4352)** course at Texas Tech University. The goal of this assignment is to implement multithreading with **mutex locks** or **semaphores** to process integers from an input file and write them to various output files based on specific conditions, ensuring concurrency between threads.

## Problem Statement
Write a C/C++ program that reads signed integer data from a file, processes each integer based on its properties, and writes them to one or more output files. The program should run across at least two concurrent threads: one to read the data into a buffer and another to process the data and write it to the corresponding files. The solution must use **mutex locks** or **semaphores** to prevent interference between threads.

## Assignment Overview

1. **Assignment 4: Multithreading**
   - **Topic:** Multithreading and Mutex/Semaphores
   - **Description:** This assignment requires the use of **multithreading** to handle file reading and processing concurrently. Data from an input file is categorized and written to several output files based on its properties (e.g., even/odd, positive/negative, square/cube). The solution must ensure thread safety and concurrent execution.

## Project Structure
- **ass4.cpp**: The main C++ program that implements multithreading, reading integers from the input file, and writing them to the appropriate output files.
- **Makefile**: The makefile used to compile the source code into an executable named `assignment_4`.
- **CS4352 - Assignment 4.pdf**: The detailed assignment instructions.

## Input/Output
### Input File Specification
- A plain text file containing signed 32-bit integers (one per line).
- Example: -34916

### Output Files
The program will generate several output files:
1. **even.out**: Contains even integers.
2. **odd.out**: Contains odd integers.
3. **positive.out**: Contains positive integers.
4. **negative.out**: Contains negative integers.
5. **square.out**: Contains perfect squares.
6. **cube.out**: Contains perfect cubes.

## Built With
This assignment utilizes:
- <a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" width="36" height="36" alt="C Programming" /></a> **C/C++**: The core programming languages used for multithreading and file handling.
- **Makefiles**: Used to compile the C++ program on HPCC.

## How to Use
1. Clone the repository:
  ```bash
  git clone https://github.com/your-repo/operating-systems.git
  cd assignment_4
  ```
2. Compile the program using the Makefile:
  ```bash
  make
  ```
3. Run the program with the input file as an argument:
  ```bash
  ./assignment_4 numbers.txt
  ```

## Learning Outcomes
By completing this assignment, I gained practical experience in:

- **Multithreading**: Implemented multiple threads to handle file I/O and data processing simultaneously, improving my understanding of concurrent execution.
- **Thread Synchronization**: Mastered the use of **mutex locks** and **semaphores** to ensure thread safety and prevent data corruption in multithreaded environments.
- **File Handling & Data Processing**: Gained proficiency in reading data from files, processing it based on specific criteria, and writing the results to multiple output files, all while ensuring that the output order is maintained.
- **Efficient Computing**: Optimized the program for high performance, ensuring it can handle large input files and make efficient use of system resources.

These experiences enhanced my ability to implement concurrency and solve problems involving large-scale data processing.

