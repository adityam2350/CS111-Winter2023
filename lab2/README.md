# You Spin Me Round Robin
The purpose of this program is to model round robin scheduling by outputting
the average waiting time and average response time given a set of processes
with arrival times and burst times.

## Building
To build your program, you can run:
make

## Running
Insert the process data into a text file with the following format.

Number of processes to run on the cpu
PID of process 1, Arrival Time of proceess 1, Burst Time of process 1
...
PID of process n, Arrival Time of proceess n, Burst Time of process n

Then run ./rr NAME_OF_YOUR_TEXT_FILE DESIRED_QUANTUM_LENGTH

In standard output, the average waitng time and response time is displayed

## Cleaning up
You can clean your workspace of all .o files and executables by running
make clean