# Operating Systems - Final Project: Elevator Operating System
![Image](https://github.com/Dhruvbam/Operating-Systems/blob/main/Images/fpss.jpg)

## About
This project is part of the **Operating Systems (CS 4352)** course at Texas Tech University. The objective of this final project is to develop a **C/C++ scheduler** for an **Elevator Operating System** that communicates asynchronously with a Python-based system via API calls. The scheduler is responsible for managing multiple elevators in a building, optimizing the flow of passengers across various floors.

## Problem Statement
The task is to implement a scheduling system that coordinates elevator movements based on input data retrieved from APIs. The solution must manage the assignment of passengers to elevators using **multithreading** to handle communication and decision-making concurrently. The program must accept a building configuration file as a command-line argument, and the elevator operations should be handled through asynchronous API calls.

## Project Overview

1. **Final Project: Elevator Operating System**
   - **Topic:** Multithreading and API Communication
   - **Description:** This project involves developing a **multithreaded scheduler** that coordinates elevators in a building by communicating with a Python-based Elevator OS via APIs. The scheduler must handle real-time data from APIs to assign passengers to elevators efficiently.

## Project Structure
- **main.cpp**: The main C++ program that implements the scheduler, handles API communication, and optimizes elevator usage through multithreading.
- **Makefile**: The Makefile used to compile the source code into an executable named `scheduler_os`.
- **CS4352 - Final Project.pdf**: The detailed final project instructions.

## Key Requirements
- **Multithreading**: The solution must use at least 3 threads:
  1. **Input Communication Thread**: Handles communication with the `/NextInput` API to retrieve passenger data.
  2. **Output Communication Thread**: Communicates with the `/AddPersonToElevator` API to assign passengers to elevators.
  3. **Scheduler Computation Thread**: Makes decisions based on the input data and coordinates with the other threads.
  
- **Asynchronous API Communication**: The scheduler must communicate with the Elevator Operating System using asynchronous API calls to manage elevator movements.

- **Input Format**: The program accepts a building configuration file (`.bldg`) as input, which contains details about elevator bays, floors, and capacity.

### Building Configuration File (.bldg)
- **Elevator Bay Name**: Alphanumeric identifier for each elevator bay.
- **Lowest and Highest Floors**: The range of floors that the elevator services.
- **Current Floor**: The floor the elevator starts on when the simulation begins.
- **Total Capacity**: The maximum number of passengers an elevator can hold.

## API Endpoints
1. **/NextInput**: Retrieves the next passenger in the queue.
2. **/AddPersonToElevator**: Assigns a passenger to an elevator.
3. **/Simulation/start**: Starts the elevator simulation.
4. **/Simulation/stop**: Stops the simulation.

## Built With
This project utilizes:
- <a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" width="36" height="36" alt="C Programming" /></a> **C/C++**: The core programming languages used to implement the multithreaded scheduler.
- **Makefiles**: Used to compile the program on the HPCC.

## How to Use
1. Clone the repository:
    ```bash
    git clone https://github.com/your-repo/operating-systems.git
    cd final_project
    ```
2. Compile the program using the Makefile:
    ```bash
    make
    ```
3. Run the scheduler with the building configuration file as an argument:
    ```bash
    ./scheduler_os building_config.bldg
    ```

## Learning Outcomes
By completing this final project, I developed key skills in:

- **Multithreading**: Designed a multithreaded application to handle real-time data processing, enabling efficient scheduling and communication between threads.
- **Asynchronous API Communication**: Gained hands-on experience using asynchronous API calls to manage data flow between the scheduler and the Elevator Operating System, ensuring smooth and timely operations.
- **Real-Time Decision Making**: Improved my ability to design systems that make real-time scheduling decisions based on continuous input from multiple data sources.
- **System Optimization**: Focused on optimizing the scheduler to ensure the simulation meets specific runtime and performance constraints, ensuring efficient resource allocation and minimal delays in the elevator system.

This project deepened my understanding of multithreading, asynchronous communication, and real-time systems in a large-scale simulation environment.
