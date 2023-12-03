add_executable(Year2022Day03 solve.c)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(Year2022Day03 PRIVATE advent)
