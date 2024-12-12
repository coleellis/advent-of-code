# Advent Of Code -- ASM

This is the newest language I've started and will take the longest time to complete. These take lots of brainpower and are no fun to debug.

The goal of this challenge is to make real puzzles of Advent of Code. These Assembly tasks are not allowed to use `glibc`, but rather only the standard x64 system calls and my own custom-made functions.

### Libraries

There are two major files here that support these challenges:

- `macros.inc`: This contains constant definitions and function macros. I choose to make simple functions macros to avoid cluttering the call stack and make debugging easier. The major constants I use are the default file descriptors and syscall table.
- `common.inc`: These are the functions I use most often. This includes opening a file and returning its file descriptor, printing an integer to the console (`printf` replica), etc. Since I really only use this for the purpose of AOC, I limit the parameters being used here. The file is always opened with `O_RDONLY` and the number printed is always an integer.
