add_executable(Year2023Day03 solve.c)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(Year2023Day03 PRIVATE advent)
