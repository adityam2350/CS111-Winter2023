## UID: 123456789
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

# Hash Hash Hash

One line description of this code.

## Building

Explain briefly how to build your program.

## Running

Show an example run of your (completed) program on using the `-t` and `-s` flags
of a run where the base hash table completes in between 1-2 seconds.

## First Implementation

Describe your first implementation strategy here (the one with a single mutex).
Argue why your strategy is correct.

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

Explain briefly how to clean up all binary files.
