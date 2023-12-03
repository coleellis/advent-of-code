cmake_minimum_required(VERSION 3.24)
project(AdventOfCode C)

set(CMAKE_C_STANDARD 99)

# add custom library
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(advent STATIC "advent.c" advent.h)

add_subdirectory(2022)
add_subdirectory(2023)