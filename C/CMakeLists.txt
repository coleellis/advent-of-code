cmake_minimum_required(VERSION 3.24)
project(AdventOfCode C)

# Set Compiler Options
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -pedantic")

# Advent Static Library
include_directories(${CMAKE_SOURCE_DIR})
add_library(advent STATIC "advent.c" "common.c" common.h advent.h)

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Definitions
add_definitions(-D_GNU_SOURCE)

# Get all subdirectories
file(GLOB YEARS LIST_DIRECTORIES true RELATIVE ${CMAKE_SOURCE_DIR} */)

foreach(YEAR_DIR ${YEARS})
    # Check if the directory contains a CMakeLists.txt file, skip if so
    if (EXISTS "${CMAKE_SOURCE_DIR}/${YEAR_DIR}/CMakeLists.txt")
        continue()
    endif()

    # Find all day source files in the directory
    file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/${YEAR_DIR}/day*.c")

    # Copy input files
    file(GLOB INPUT_FILES "${CMAKE_SOURCE_DIR}/${YEAR_DIR}/*.txt")
    foreach(INPUT_FILE ${INPUT_FILES})
        get_filename_component(INPUT_FILENAME ${INPUT_FILE} NAME_WE)
        configure_file(${INPUT_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${YEAR_DIR}/${INPUT_FILENAME}.txt COPYONLY)
    endforeach()

    # Add executables for each day
    foreach(SOURCE_FILE ${SOURCES})
        get_filename_component(DAY_NAME ${SOURCE_FILE} NAME_WE)
        set(EXECUTABLE_NAME "${YEAR_DIR}_${DAY_NAME}")
        add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
        target_compile_options(${EXECUTABLE_NAME} PRIVATE -O3 -g -Wall -Wextra -pedantic)

        # Link the advent static library
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE advent curl)

        # Set output directory per year
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${YEAR_DIR}"
        )
    endforeach()
endforeach()
