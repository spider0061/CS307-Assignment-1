# CS307-Assignment-1
### This repository is dedicated for assignment 1 of CS307 course.
Instructor: Dr. Aditya Nigam


### Team Members

|   | Name | Roll No.  |
|--------|--------|--------|
|A| Ashutosh Sharma  | B18010 |
|B| Anuj Goel    | B18161  |
|C| Om Pandey | B18182  |

Assignment problem sheet: [Assignment Questions](https://drive.google.com/file/d/1QdCapIXOi28YPmmpFEJ9avKOisWNZz5y/view?usp=sharing)

### Requirements
gcc version: 9.3

**Libraries used-**

Q1: Creating a shell.
1. #include <sys/wait.h>
2. #include <sys/types.h>
3. #include <unistd.h>
4. #include <stdlib.h>
5. #include <stdio.h>
6. #include <string.h>
7. #include <dirent.h>

Q2: Dining students problem
1. #include <pthread.h>
2. #include <stdio.h>
3. #include <unistd.h>
4. #include <time.h>
5. #include <stdlib.h>

Q3: Matrix Multiplication
1. #include<bits/stdc++.h>
2. #include<pthread.h>
3. #include<time.h>
4. #include<iostream>
5. #include<stdio.h>
6. #include<stdlib.h>
  
### Q1. Creating a shell.
In this question we have to create a shell which supports the following commands:
1. clr: To clear the screen.
2. pause: To pause operations of the shell until ENTER is pressed.
3. help: To show the help menu.
4. quit / Ctrl+D: To quit the shell.
5. history: To print all the  previous commands used in the shell.
6. cd <directory>: To move to <directory>. If the directory is not present it will out current address.
7. dir <directory>: To list the contents of <directory>.
8. environ: To print environment variables of bash and current shell.
9. echo <comment>: To print <comment> on screen. 
10. Add  shell environment variables to it.
11. Shell can take commands from a batchfile.

**Steps to run the shell:**
1. Enter the Q1 folder.
2. Type "make" on terminal.
3. Then type "./shell" on terminal. or type "./shell <batch-file-name>" if you have a batch-file.
4. The shell is running.

### Q2. Dining students problem
This problem is similar to dining philosphers problem but it has the following states:
Use threads with locks to simulate the students eat-think lifecycle. There are 4 states for
each student:
1. Waiting for Spoons
2. One spoon acquired.
3. Both spoons acquired and Eating (20 seconds)
4. Thinking (< 2 seconds)
  
**Steps to run the program:**
1. Enter the Q2 folder.
2. Type make on terminal.
3. Then type "./prog" on terminal.
4. The program is running and it will output the initial states of all students and when state od any student changes.

### Q3. Matrix Multiplication
Write a sequential program to multiply two square matrices. Initialize the matrices with any
random values. The size of matrix (n) should be taken as command line argument. Now
write a parallel program using threads to do the same. Run both programs for different
values of n (n=1 to at least 3000) and make proper log of respective running time.

**Input**
n = size of the square matrix

**Output**
Create a report which includes the graph of input size (n) vs running times for both
programs. Run each program at least 5 times and use average running time for analysis.
Discuss your inferences.

**Steps to run the program:**
1. Enter the Q3 folder.
2. Type make on terminal.
3. Then type "./simp" on terminal for simple multiplication.
4. Then type "./base" on terminal for parallel multiplication.
