cmake_minimum_required(VERSION 3.24)
project(Year2023 C)

set(CMAKE_C_STANDARD 99)
set(IN_DIR "${CMAKE_SOURCE_DIR}/_input/2023")
set(OUT_DIR "${CMAKE_BINARY_DIR}/2023")

# day 1
add_executable(2023-Day01 day01.c)
configure_file(${IN_DIR}/day01.txt ${OUT_DIR}/day01.txt COPYONLY)
target_link_libraries(2023-Day01 PRIVATE advent)

# day 2
add_executable(2023-Day02 day02.c)
configure_file(${IN_DIR}/day02.txt ${OUT_DIR}/day02.txt COPYONLY)
target_link_libraries(2023-Day02 PRIVATE advent)

# day 3
add_executable(2023-Day03 day03.c)
configure_file(${IN_DIR}/day03.txt ${OUT_DIR}/day03.txt COPYONLY)
target_link_libraries(2023-Day03 PRIVATE advent)

# day 4
add_executable(2023-Day04 day04.c)
configure_file(${IN_DIR}/day04.txt ${OUT_DIR}/day04.txt COPYONLY)
target_link_libraries(2023-Day04 PRIVATE advent)

# day 5
add_executable(2023-Day05 day05.c)
configure_file(${IN_DIR}/day05.txt ${OUT_DIR}/day05.txt COPYONLY)
target_link_libraries(2023-Day05 PRIVATE advent)

# day 6
add_executable(2023-Day06 day06.c)
configure_file(${IN_DIR}/day06.txt ${OUT_DIR}/day06.txt COPYONLY)
target_link_libraries(2023-Day06 PRIVATE advent)

# day 7
add_executable(2023-Day07 day07.c)
configure_file(${IN_DIR}/day07.txt ${OUT_DIR}/day07.txt COPYONLY)
target_link_libraries(2023-Day07 PRIVATE advent)

# day 8
add_executable(2023-Day08 day08.c)
configure_file(${IN_DIR}/day08.txt ${OUT_DIR}/day08.txt COPYONLY)
target_link_libraries(2023-Day08 PRIVATE advent)

# day 9
add_executable(2023-Day09 day09.c)
configure_file(${IN_DIR}/day09.txt ${OUT_DIR}/day09.txt COPYONLY)
target_link_libraries(2023-Day09 PRIVATE advent)

# day 10
add_executable(2023-Day10 day10.c)
configure_file(${IN_DIR}/day10.txt ${OUT_DIR}/day10.txt COPYONLY)
target_link_libraries(2023-Day10 PRIVATE advent)

# day 11
add_executable(2023-Day11 day11.c)
configure_file(${IN_DIR}/day11.txt ${OUT_DIR}/day11.txt COPYONLY)
target_link_libraries(2023-Day11 PRIVATE advent)

# day 12
add_executable(2023-Day12 day12.c)
configure_file(${IN_DIR}/day12.txt ${OUT_DIR}/day12.txt COPYONLY)
target_link_libraries(2023-Day12 PRIVATE advent)

# day 13
add_executable(2023-Day13 day13.c)
configure_file(${IN_DIR}/day13.txt ${OUT_DIR}/day13.txt COPYONLY)
target_link_libraries(2023-Day13 PRIVATE advent)

# day 14
add_executable(2023-Day14 day14.c)
configure_file(${IN_DIR}/day14.txt ${OUT_DIR}/day14.txt COPYONLY)
target_link_libraries(2023-Day14 PRIVATE advent)

# day 15
add_executable(2023-Day15 day15.c)
configure_file(${IN_DIR}/day15.txt ${OUT_DIR}/day15.txt COPYONLY)
target_link_libraries(2023-Day15 PRIVATE advent)