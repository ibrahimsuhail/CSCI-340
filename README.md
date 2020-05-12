# CSCI-340

RoundRobin.cpp

Instructions to compile and generate the executable file.

Download cpp file
Open terminal and enter:
g++ (paste filepath) 
This creates an executable file a.out

To execute: 
./a.out
A discussion on how you got the code to work and issues you encountered along the way.
The objective of this program is to implement a priority-based round robin scheduling algorithm of the previously assigned Homework problem 5.18 for the processes given
Essentially, each process is assigned a maximum time quantum that it is allowed to run. When this quantum is used up, the next highest priority process is given a chance to run.
First, I calculated the wait time for every process.
Then I Implemented a loop that incremented the time variable t from t=0 to t = 96 
This loop checked for the arrival of a process at time t by reading the Process Table from the input file. I then read the file and checked for any processes at Arrival = t. 
I traversed all processes while they were running. I increased the value of time
By the time quantum and decreased the remaining burst time by time quantum.
Once the process is finished the burst time = 0, and the wait time was calculated
Now, I printed out the file, sorted each process by its priority, found each process’ turnaround time, and printed the results.

mtrands.cpp

Instructions to compile and generate the executable file.
----Can only be compiled in a Linux environment

Open terminal and enter:
g++ (paste filepath) 
This creates an executable file a.out

To execute: 
./a.out
A discussion on how you got the code to work and issues you encountered along the way.

The objective of this program is to generate 5 threads each containing 20 subthreads in order to find the minimum value in an array of 10,000 random numbers.
Generating the 10,000 random numbers and finding the minimum without multithreading was easy to do.
I created a loop from 0-9,999 generating 10,000 random numbers and put them in an array.
Each array’s value was then put into a vector and sorted in order to place its minimum and maximum values at the beginning and end respectively. 
I would then return those values.
Using the threads to find the minimum was the more challenging part of this assignment. 
I had the most trouble with creating 20 subthreads for each 5 major threads, and finding the minimum value in each. 
However, I soon realized that each of my 5 major threads should call a function creating 20 subthreads, totalling 100 threads in all.
Each subthread would call a function finding its minimum element, and this minimum element would be then placed into an array. 
This array would contain the minimum value from each thread. 
I then sorted this array and found the minimum value.

time.c

Instructions to compile and generate the executable file.

----On windows:
To compile C program time.c, and create an executable file called time, enter in command prompt:
gcc time.c -o time

OR
cc time.c -o time

To execute program time, enter:
./time

To use this program to find the time it takes to run a command, enter:
./time (command)

----Linux

Open terminal and enter:
clang (paste filepath) -o time

To execute: 
./time

To use this program to find the time it takes to run a command, enter:
./time (command)


A discussion on how you got the code to work and issues you encountered along the way.
In the beginning I wanted to retrieve the user typed command from the command line like ls, ps, whoami. I was having trouble with that, but after reading the book and looking up information online, I found out that I had to use char* c = argv[1];  to finally get the command. Then I created the file descriptor array to access the pipe and found the parent’s pid. I then started the parent’s timer and ended it when I forked the child process. I now had forked the child process, found its starting time, and created the pipe. I kept track of the parent’s start and end times, and sent the starting time down the pipe to the child process. Then the child would read the message from the pipe and print out the parent’s starting time. Finally, I would print out the name of the command, the child’s starting time, the parent’s starting time (as received from pipe), parent’s ending time, and parent’s elapsed time.

