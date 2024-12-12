# Advent of Code -- C

I've been writing the C challenges as a second pass because I first attempt for speed (Python).

These challenges are written in C99 and use `-GNU_SOURCE` for its API. These challenges are built using CMake and tested on a Mac and (Debian) Linux machine.

## Build Process

As of 2024, I built an automatic CMake file to automatically build all challenges. This is much improved from the earlier CMake implementation because for each new challenge, I had to build a new executable in the _CMakeLists.txt_ and link the libraries. Either way, CMake rebuilds every project in the directory; however, CMake's caching speeds the process to only build changed files since the last build.

I use a build script for this on Linux that replicates the default CLion build process. This puts all the build files into `cmake-build-debug` and executables in `bin`. This also generates `compile_commands.json` for use with Neovim LSPs (otherwise, they won't understand the `advent.h` include file). I have this build script in my `/usr/.local/bin` on all my Unix machines.

## Utility Library

I first started Advent in 2022 where I attempted to write the most Python-esque solutions. In [common.h](./common.h) and [common.c](./common.c), many functions replicate Python behaviors for string parsing.

For most challenges in 2023, I parsed the `FILE *` directly using `getline()` to either build the data structure or perform the instruction for that line (challenge dependent). This is a strong solution but also convoluted the directory with loads of input files. For the time being, this solution is fine. Python is already using the `aocd` library at this point, so I'm only cloning the input file for C.

In 2024, I started writing the AOC API ([advent.h](./advent.h) and [advent.c](./advent.c)) to automatically get data from the website. This means I'm now parsing the data as a string rather than a `FILE *`. This doesn't change my implementations that much; I simply use `strchr(line, '\n')` to get the line and then parse that line individually. This provides new developers some more understanding without reading the `man` pages, since functions like `getline` make implicit calls to `malloc`.
