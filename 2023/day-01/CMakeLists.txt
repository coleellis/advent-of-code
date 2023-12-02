cmake_minimum_required(VERSION 3.24)
project(Year2023Day01 C)

set(CMAKE_C_STANDARD 99)

add_executable(Year2023Day01 solve.c)
configure_file(input.txt input.txt COPYONLY)
