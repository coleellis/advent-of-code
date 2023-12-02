cmake_minimum_required(VERSION 3.24)
project(Year2022Day05 C)

set(CMAKE_C_STANDARD 99)

add_executable(Year2022Day05 solve.c)
configure_file(input.txt input.txt COPYONLY)
