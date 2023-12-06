add_executable(Year2023Day06 solve.c)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(Year2023Day06 PRIVATE advent)
