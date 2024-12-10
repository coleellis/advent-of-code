cmake_minimum_required(VERSION 3.24)
project(AdventOfCode ASM_NASM)

# Set Compiler Options
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf64 -I${CMAKE_CURRENT_SOURCE_DIR}/include")

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Get all subdirectories
file(GLOB YEARS LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */)

foreach(YEAR_DIR ${YEARS})
    # Make sure we're not hitting the year directory
    if(${YEAR_DIR} STREQUAL "include")
        continue()
    endif()

    # Find all source files
    file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR_DIR}/day*.asm")

    # Copy input files
    file(GLOB INPUT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${YEAR_DIR}/*.txt")
    foreach(INPUT_FILE ${INPUT_FILES})
        get_filename_component(INPUT_FILENAME ${INPUT_FILE} NAME_WE)
        configure_file(${INPUT_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${YEAR_DIR}/${INPUT_FILENAME}.txt COPYONLY)
    endforeach()

    # Add executable for each day
    foreach(SOURCE_FILE ${SOURCES})
        get_filename_component(DAY_NAME ${SOURCE_FILE} NAME_WE)
        set(EXECUTABLE_NAME "${YEAR_DIR}_${DAY_NAME}")
        add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})

        # Set output directory per year
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${YEAR_DIR}"
        )
    endforeach()
endforeach()
