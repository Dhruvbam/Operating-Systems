# Operating Systems - Assignment 2: Bash, Makefiles, and Utilizing the HPCC
![Image](https://github.com/Dhruvbam/Operating-Systems/blob/main/Images/assignment2.jpg)

## About
This project is part of the **Operating Systems (CS 4352)** course at Texas Tech University. The goal of this assignment is to automate file decryption and transformation tasks on the **HPCC** using a **Bash script** and a **Makefile**, utilizing GNU 5.4.0 for job submission and execution in a high-performance computing environment.

## Problem Statement
The task involves creating a submission script for the HPCC that performs specific actions, such as decrypting a file, transforming data using compiled C++ and C programs, and appending the Nth line from the output to a results file.

## Assignment Overview

1. **Assignment 2: Bash, Makefiles, and Utilizing the HPCC**
   - **Topic:** Bash Scripting and Makefiles
   - **Description:** This assignment involves writing a Bash script that automates file decryption, transformation, and data extraction on the **HPCC** using SLURM for job scheduling. The task requires integrating precompiled C and C++ binaries to process the data and output results to a file.

## Project Structure
- **assignment_2.sh**: The main Bash script that performs the decryption, data transformation, and appends the result to `a2_results.txt`.
- **decrypt**: A compiled C++ program used to decrypt the provided file.
- **transform**: A compiled C program used to transform data and provide the line number for extraction.

## Built With
This assignment utilizes:
- <a href="https://www.gnu.org/software/bash/" target="_blank" rel="noreferrer"><img src="https://img.shields.io/badge/Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" width="36" height="36" alt="Bash" /></a> **Bash**: For scripting and task automation on the HPCC.
- **C/C++**: Precompiled binaries are used to decrypt and transform files as part of the task.

## How to Use
1. Clone the repository:
    ```bash
    git clone https://github.com/your-repo/operating-systems.git
    cd assignment_2
    ```
2. Submit the job to **SLURM** using the following command:
    ```bash
    sbatch assignment_2.sh
    ```

## Learning Outcomes
By completing this assignment, I gained valuable experience in:

- **Bash Scripting**: Enhanced my ability to write efficient **Bash scripts** to automate complex workflows, including job scheduling, file manipulation, and process control in a distributed environment.
- **File Handling & Data Processing**: Gained hands-on experience working with **compiled C/C++ programs** for file decryption and transformation, while managing file input/output operations using automation tools.
- **HPCC & SLURM Proficiency**: Acquired in-depth knowledge of working with **High-Performance Computing Clusters (HPCC)** and using **SLURM** for job scheduling and resource management, a critical skill in large-scale computing environments.
- **Automation & Workflow Optimization**: Learned how to integrate precompiled binaries into a larger automated workflow, streamlining the process from decryption to data extraction with a focus on efficiency and scalability.
- **Makefile Usage**: Developed the ability to use **Makefiles** to automate the compilation process and manage project dependencies, improving development workflow efficiency in a collaborative environment.

These experiences have strengthened my skills in task automation, scripting, and managing large computing tasks in distributed systems.
