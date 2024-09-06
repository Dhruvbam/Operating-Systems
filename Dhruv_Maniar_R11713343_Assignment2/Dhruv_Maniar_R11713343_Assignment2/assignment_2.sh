#!/bin/bash -

#=====================================================================
#title        : assignment_2.sh
#description  : This script decrypts an encrypted file and appends the Nth line to a result file.
#author       : Dhruv Maniar
#date         : 02/13/2024
#version      : 1.0
#usage        : sbatch assignment_2.sh
#notes        : Script for CS4352 assignment 2.
#bash_version : 4.2.46(2)-release
#=====================================================================

#SBATCH --job-name=cs4352_a2
#SBATCH --partition=quanah
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem-per-cpu=5370MB
#SBATCH --time=00:05:00

# Load the required GNU 5.4.0 module
module load gnu/5.4.0

# Print Full Name and R# into a2_results.txt
echo "Dhruv Maniar" > a2_results.txt
echo "R11713343" >> a2_results.txt

# Change permissions to ensure executables can run
chmod +x decrypt
chmod +x transform
chmod +x assignment_2.sh

# Execute decrypt and transform applications
DECRYPTED_PATH=$(./decrypt /lustre/work/errees/courses/cs4352/assignment2/input/encrypted.txt)
TRANSFORMED_LINE=$(./transform 11713343)

# Append the Nth line from the decrypted file path to a2_results.txt
NTH_LINE=$(sed -n "${TRANSFORMED_LINE}p" "${DECRYPTED_PATH}")
echo "${NTH_LINE}" >> a2_results.txt

# End of the script
echo "${NTH_LINE}"
echo "Script execution completed."
