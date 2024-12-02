cmake_minimum_required(VERSION 3.24)
project(AdventOfCode C)

set(CMAKE_C_STANDARD 99)

# add custom library
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(advent STATIC "advent.c" advent.h)

add_subdirectory(2015)
add_subdirectory(2016)
add_subdirectory(2017)
add_subdirectory(2018)
add_subdirectory(2019)
add_subdirectory(2020)
add_subdirectory(2021)
add_subdirectory(2022)
add_subdirectory(2023)