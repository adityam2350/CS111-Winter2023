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

When working with 1 thread, the difference between the base and v1 implementation is comparable, with v1 being a little worse due to the overhead of locking. But when, the number of threads is more than or equal to 2, the the v1 approach becomes significantly worse, due to the high overhead associated with managing locking between multiple threads and the fact that the entire hash table is locked on each add_entry call. 

## Second Implementation

Here, instead of placing the lock in the hash_table struct, I placed the lock in the hash_table_entry struct and moved the lock and unlock calls such that only the addition of a node to the SLIST is the only line of code between the two methods. This works because the only collisions that are occur are between accesses that attempt to the same SLIST. So we can ignore acceses of different HTEs because we are sure they won't cause a race conditon .

### Performance

When working with the number of cores on my machine which is 4, the speed up is by a factor 3.16. The increase in performacne is the fact that with our second implementation, we are exposing more parallelism because we aren't locking the hash table on every add_entry call like we are doing in our first implementation. This is overkill and kills all of the parallelism. By reducing the granularity of the lock to the hash_table_entry level and moving where the locks are locked and unlocked, we actually allow add_entry calls to occur in parallel, significantly reduce the execution time.

## Cleaning up

You can clean up with a simple call to "make clear"
