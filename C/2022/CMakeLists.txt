cmake_minimum_required(VERSION 3.24)
project(Year2022 C)

set(CMAKE_C_STANDARD 99)
set(IN_DIR "${CMAKE_SOURCE_DIR}/_input/2022")
set(OUT_DIR "${CMAKE_BINARY_DIR}/2022")

# day 1
add_executable(2022-Day01 day01.c)
configure_file(${IN_DIR}/day01.txt ${OUT_DIR}/day01.txt COPYONLY)
target_link_libraries(2022-Day01 PRIVATE advent)

# day 2
add_executable(2022-Day02 day02.c)
configure_file(${IN_DIR}/day02.txt ${OUT_DIR}/day02.txt COPYONLY)
target_link_libraries(2022-Day02 PRIVATE advent)

# day 3
add_executable(2022-Day03 day03.c)
configure_file(${IN_DIR}/day03.txt ${OUT_DIR}/day03.txt COPYONLY)
target_link_libraries(2022-Day03 PRIVATE advent)

# day 4
add_executable(2022-Day04 day04.c)
configure_file(${IN_DIR}/day04.txt ${OUT_DIR}/day04.txt COPYONLY)
target_link_libraries(2022-Day04 PRIVATE advent)

# day 5
add_executable(2022-Day05 day05.c)
configure_file(${IN_DIR}/day05.txt ${OUT_DIR}/day05.txt COPYONLY)
target_link_libraries(2022-Day05 PRIVATE advent)

# day 6
add_executable(2022-Day06 day06.c)
configure_file(${IN_DIR}/day06.txt ${OUT_DIR}/day06.txt COPYONLY)
target_link_libraries(2022-Day06 PRIVATE advent)

# day 8
add_executable(2022-Day08 day08.c)
configure_file(${IN_DIR}/day08.txt ${OUT_DIR}/day08.txt COPYONLY)
target_link_libraries(2022-Day08 PRIVATE advent)

# day 9
add_executable(2022-Day09 day09.c)
configure_file(${IN_DIR}/day09.txt ${OUT_DIR}/day09.txt COPYONLY)
target_link_libraries(2022-Day09 PRIVATE advent)

# day 10
add_executable(2022-Day10 day10.c)
configure_file(${IN_DIR}/day10.txt ${OUT_DIR}/day10.txt COPYONLY)
target_link_libraries(2022-Day10 PRIVATE advent)

# day 12
add_executable(2022-Day12 day12.c)
configure_file(${IN_DIR}/day12.txt ${OUT_DIR}/day12.txt COPYONLY)
target_link_libraries(2022-Day12 PRIVATE advent)