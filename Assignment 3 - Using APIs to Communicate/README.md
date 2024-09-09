# Operating Systems - Assignment 3: Using APIs to Communicate
![Image](https://github.com/Dhruvbam/Operating-Systems/blob/main/Images/ass3.jpg)

## About
This project is part of the **Operating Systems (CS 4352)** course at Texas Tech University. The goal of this assignment is to develop a C/C++ program that interacts with APIs hosted in a singularity container on the HPCC. The program communicates via **GET** and **PUT** requests, sending and retrieving data from the **/initialize** and **/modify** APIs.

## Problem Statement
Using the code provided as a template, the task is to modify and expand the program to communicate with the **/initialize** and **/modify** APIs through **PUT** and **GET** requests. The program must perform a sequence of data exchanges, printing values to standard output, and construct a **Makefile** to compile the program into a binary executable named `assignment_3`.

## Assignment Overview

1. **Assignment 3: Using APIs to Communicate**
   - **Topic:** API Communication in C/C++
   - **Description:** This assignment involves writing a C/C++ program that communicates with APIs in a **singularity container**. The program must perform a series of **GET** and **PUT** requests to modify and retrieve integer values from the provided APIs. Additionally, the assignment includes constructing a **Makefile** to compile the source code into an executable.

## Project Structure
- **assignment_3.cpp**: The C++ program that communicates with the **/initialize** and **/modify** APIs using **GET** and **PUT** requests.
- **Makefile**: The Makefile used to compile the source code into a binary executable named `assignment_3`.
- **CS4352 - Assignment 3.pdf**: The detailed assignment instructions.

## API Definitions
1. **/initialize**:
   - **PUT**: Accepts an integer to initialize the internal data object.
   - **GET**: Returns the altered form of the integer you supplied to **PUT**.

2. **/modify**:
   - **PUT**: Accepts an integer to modify the internal data object.
   - **GET**: Returns the altered form of the integer you supplied to **PUT**.

## Built With
This assignment utilizes:
- <a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" width="36" height="36" alt="C Programming" /></a> **C/C++**: The core programming languages used to interact with the APIs.
- **Makefiles**: Used to automate the compilation process on the HPCC.

## How to Use
1. Clone the repository:
    ```bash
    git clone https://github.com/your-repo/operating-systems.git
    cd assignment_3
    ```
2. Compile the program using the Makefile:
    ```bash
    make
    ```
3. Submit the job to **SLURM** using the provided Bash script or run the binary directly:
    ```bash
    sbatch assignment_3.sh
    ```

## Learning Outcomes
By completing this assignment, I gained valuable experience in:

- **API Communication**: Mastered sending and retrieving data using **GET** and **PUT** requests to interact with APIs, applying real-world API communication concepts in a system-level programming context.
- **C/C++ Programming**: Gained hands-on experience modifying and building C/C++ applications, with a focus on external communication and handling HTTP-like requests.
- **Makefile Expertise**: Developed proficiency in writing **Makefiles** to automate compilation, ensuring an efficient development workflow on high-performance computing systems.
- **HPCC & SLURM Integration**: Enhanced my understanding of deploying and running jobs on **HPCC** using **SLURM**, learning how to submit jobs for programs that require external API environments.

These skills have strengthened my ability to work on system-level programming tasks that require integration with external APIs.
