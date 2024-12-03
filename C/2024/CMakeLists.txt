cmake_minimum_required(VERSION 3.24)
project(Year2024 C)

set(CMAKE_C_STANDARD 99)
set(IN_DIR "${CMAKE_SOURCE_DIR}/_input/2024")
set(OUT_DIR "${CMAKE_BINARY_DIR}/2024")

# day 1
add_executable(2024-Day01 day01.c)
configure_file(${IN_DIR}/day01.txt ${OUT_DIR}/day01.txt COPYONLY)
target_link_libraries(2024-Day01 PRIVATE advent)

# day 2
add_executable(2024-Day02 day02.c)
configure_file(${IN_DIR}/day02.txt ${OUT_DIR}/day02.txt COPYONLY)
target_link_libraries(2024-Day02 PRIVATE advent)

# day 3
add_executable(2024-Day03 day03.c)
configure_file(${IN_DIR}/day03.txt ${OUT_DIR}/day03.txt COPYONLY)
target_link_libraries(2024-Day03 PRIVATE advent)

# day 4
add_executable(2024-Day04 day04.c)
configure_file(${IN_DIR}/day04.txt ${OUT_DIR}/day04.txt COPYONLY)
target_link_libraries(2024-Day04 PRIVATE advent)

# day 5
add_executable(2024-Day05 day05.c)
configure_file(${IN_DIR}/day05.txt ${OUT_DIR}/day05.txt COPYONLY)
target_link_libraries(2024-Day05 PRIVATE advent)

# day 6
add_executable(2024-Day06 day06.c)
configure_file(${IN_DIR}/day06.txt ${OUT_DIR}/day06.txt COPYONLY)
target_link_libraries(2024-Day06 PRIVATE advent)

# day 7
add_executable(2024-Day07 day07.c)
configure_file(${IN_DIR}/day07.txt ${OUT_DIR}/day07.txt COPYONLY)
target_link_libraries(2024-Day07 PRIVATE advent)

# day 8
add_executable(2024-Day08 day08.c)
configure_file(${IN_DIR}/day08.txt ${OUT_DIR}/day08.txt COPYONLY)
target_link_libraries(2024-Day08 PRIVATE advent)

# day 9
add_executable(2024-Day09 day09.c)
configure_file(${IN_DIR}/day09.txt ${OUT_DIR}/day09.txt COPYONLY)
target_link_libraries(2024-Day09 PRIVATE advent)

# day 10
add_executable(2024-Day10 day10.c)
configure_file(${IN_DIR}/day10.txt ${OUT_DIR}/day10.txt COPYONLY)
target_link_libraries(2024-Day10 PRIVATE advent)

# day 11
add_executable(2024-Day11 day11.c)
configure_file(${IN_DIR}/day11.txt ${OUT_DIR}/day11.txt COPYONLY)
target_link_libraries(2024-Day11 PRIVATE advent)

# day 12
add_executable(2024-Day12 day12.c)
configure_file(${IN_DIR}/day12.txt ${OUT_DIR}/day12.txt COPYONLY)
target_link_libraries(2024-Day12 PRIVATE advent)

# day 13
add_executable(2024-Day13 day13.c)
configure_file(${IN_DIR}/day13.txt ${OUT_DIR}/day13.txt COPYONLY)
target_link_libraries(2024-Day13 PRIVATE advent)

# day 14
add_executable(2024-Day14 day14.c)
configure_file(${IN_DIR}/day14.txt ${OUT_DIR}/day14.txt COPYONLY)
target_link_libraries(2024-Day14 PRIVATE advent)

# day 15
add_executable(2024-Day15 day15.c)
configure_file(${IN_DIR}/day15.txt ${OUT_DIR}/day15.txt COPYONLY)
target_link_libraries(2024-Day15 PRIVATE advent)

# day 16
add_executable(2024-Day16 day16.c)
configure_file(${IN_DIR}/day16.txt ${OUT_DIR}/day16.txt COPYONLY)
target_link_libraries(2024-Day16 PRIVATE advent)

# day 17
add_executable(2024-Day17 day17.c)
configure_file(${IN_DIR}/day17.txt ${OUT_DIR}/day17.txt COPYONLY)
target_link_libraries(2024-Day17 PRIVATE advent)

# day 18
add_executable(2024-Day18 day18.c)
configure_file(${IN_DIR}/day18.txt ${OUT_DIR}/day18.txt COPYONLY)
target_link_libraries(2024-Day18 PRIVATE advent)

# day 19
add_executable(2024-Day19 day19.c)
configure_file(${IN_DIR}/day19.txt ${OUT_DIR}/day19.txt COPYONLY)
target_link_libraries(2024-Day19 PRIVATE advent)

# day 20
add_executable(2024-Day20 day20.c)
configure_file(${IN_DIR}/day20.txt ${OUT_DIR}/day20.txt COPYONLY)
target_link_libraries(2024-Day20 PRIVATE advent)

# day 21
add_executable(2024-Day21 day21.c)
configure_file(${IN_DIR}/day21.txt ${OUT_DIR}/day21.txt COPYONLY)
target_link_libraries(2024-Day21 PRIVATE advent)

# day 22
add_executable(2024-Day22 day22.c)
configure_file(${IN_DIR}/day22.txt ${OUT_DIR}/day22.txt COPYONLY)
target_link_libraries(2024-Day22 PRIVATE advent)

# day 23
add_executable(2024-Day23 day23.c)
configure_file(${IN_DIR}/day23.txt ${OUT_DIR}/day23.txt COPYONLY)
target_link_libraries(2024-Day23 PRIVATE advent)

# day 24
add_executable(2024-Day24 day24.c)
configure_file(${IN_DIR}/day24.txt ${OUT_DIR}/day24.txt COPYONLY)
target_link_libraries(2024-Day24 PRIVATE advent)

# day 25
add_executable(2024-Day25 day25.c)
configure_file(${IN_DIR}/day25.txt ${OUT_DIR}/day25.txt COPYONLY)
target_link_libraries(2024-Day25 PRIVATE advent)