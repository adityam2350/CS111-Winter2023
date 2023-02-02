## UID: 805805626
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

## Pipe Up

Our goal with this lab was to built a program in c that mirrors the same behavior as the pipe "|" functionality in Linux

## Building

In order to build this program, you must ensure that the given makefile is located in the same directory as the given pipe.c file. And you simply run 'make' in the Linux terminal.

## Running

You can run this program after building it by running './pipe [ARG1] [ARG2] [ARG3] ... [ARGN]' where each ARGN is a command in the shell. For example, you can run ./pipe ls wc and it will the count of newlines, words, and bytes in the text produced by the ls command in your current directory.

## Cleaning up
You can clean up the binary files by simply running 'make clear' after which the executable and .o files will be removed from your directory.