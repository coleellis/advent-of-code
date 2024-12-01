cmake_minimum_required(VERSION 3.24)
project(Year2016 C)

set(CMAKE_C_STANDARD 99)
set(IN_DIR "${CMAKE_SOURCE_DIR}/_input/2016")
set(OUT_DIR "${CMAKE_BINARY_DIR}/2016")

# day 1
add_executable(2016-Day01 day01.c)
configure_file(${IN_DIR}/day01.txt ${OUT_DIR}/day01.txt COPYONLY)
target_link_libraries(2016-Day01 PRIVATE advent)