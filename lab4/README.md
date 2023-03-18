## UID: 805805626

(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

# Hey! I'm Filing Here

This code makes a 1MiB ext2 file system with 2 directories, 1 regular file, and 1 sym-link that can be mounted on a current directory.

## Building

You can build the program by simply running "make" in the terminal.

## Running

You can run the program by executing "./ext2-create" in the terminal. Then make a a directory "mnt" by running the "mkdir mnt" command in the terminal. You then mount the file system on the mnt directory with "sudo mount -o loop cs111-base.img mnt". Then, you rn ls -ain and will see:
total 7
2 drwxr -xr-x 3 0 0 1024 .
                         ..
13 lrw-r--r-- 1 1000 1000 11 hello -> hello -world
12 -rw-r--r-- 1 1000 1000 12 hello -world
11 drwxr -xr-x 2 0 0 1024 lost+found
(blank spaces for machine-dependent output)


## Cleaning up
You can unmount your file system by first running "sudo unmount mnt" and then, you can remove the directory "mnt" by running "rmdir mnt" in the command line. Then you can clean all .o files and executables by simply running "make clean" in the terminal.
