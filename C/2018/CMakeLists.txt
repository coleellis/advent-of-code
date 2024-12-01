cmake_minimum_required(VERSION 3.24)
project(Year2018 C)

set(CMAKE_C_STANDARD 99)
set(IN_DIR "${CMAKE_SOURCE_DIR}/_input/2018")
set(OUT_DIR "${CMAKE_BINARY_DIR}/2018")

# day 1
add_executable(2018-Day01 day01.c)
configure_file(${IN_DIR}/day01.txt ${OUT_DIR}/day01.txt COPYONLY)
target_link_libraries(2018-Day01 PRIVATE advent)