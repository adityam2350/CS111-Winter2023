## UID: 805805626
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

# Hash Hash Hash

We are attempting to create a thread-safe, concurrent implementation of a hash-table

## Building

Download all necessary source files into your directory and run "make" in your terminal

## Running


You can run the program and the effectiveness of the different implementations by running
./hash-table -t 4 -s 100000 where the argument after t represents the number of cores you would like to use and the argument 100000 represents the number of entries to add per thread. After running this with your desired arguments the output should be as follows
> ./hash-table-tester -t 8 -s 50000
Generation: 130,340 usec
Hash table base: 1,581,974 usec
- 0 missing
Hash table v1: 1,763,469 usec
- 0 missing
Hash table v2: 496,051 usec
- 0 missing

As you can see, the follwing code describes how long each implementaiton of the hash table took to run along with the number of missing entries (of which there should be none)

## First Implementation

For my first implementation strategy, I stored a lock for the entire hash table the hash_table struct. Then, I modified the code such that whenever hash_table_v1_add_entry, a thread would try to acquire a lock at the beginning of the function. If successful, it would run through the function completely before releasing the lock at the end of the funciton. If not succesful, it would wait until it could acquire the lock.
### Performance


Run the tester such that the base hash table completes in 1-2 seconds.
Report the relative speedup (or slow down) with a low number of threads and a
high number of threads. Note that the amount of work (`-t` times `-s`) should
remain constant. Explain any differences between the two.

## Second Implementation

Describe your second implementation strategy here (the one with a multiple
mutexes). Argue why your strategy is correct.

### Performance

Run the tester such that the base hash table completes in 1-2 seconds.
Report the relative speedup with number of threads equal to the number of
physical cores on your machine (at least 4). Note again that the amount of work
(`-t` times `-s`) should remain constant. Report the speedup relative to the
base hash table implementation. Explain the difference between this
implementation and your first, which respect why you get a performance increase.

## Cleaning up

You can clean up all 
