# A Kernel Seedling
Our goal with this lab was to create a kernel module that adds a file to /proc that tells us how many processes are running currently

## Building
In order to build the program, ensure that you are in the same directory as the Makefile and the proc_count.c, and simply run the command "make", which will build your program. Then to insert the module to the kernel, you run the command "sudo insmod proc_count.ko". You can check whether the module was inserted by running "sudo dmesg -l info", and the most recent message should be "proc_count: init"

## Running
In order to run the program after building and inserting the module, just type the command "cat /proc/count" and it's output will be an integer that tells us the number of processing currently running.

## Cleaning up
In order to clean up the program, you must remove the module from the kernel, which you can do by running "sudo rmmod proc_count.ko". Then to ensure that the module was removed, toy can run "sudo dmesg -l info", and the most recent message should be "proc_count: exit"

## Testing
This module was tested on Linux kernel release 5.14.8-arch1-1.