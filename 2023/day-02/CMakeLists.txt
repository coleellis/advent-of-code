add_executable(Year2023Day02 optimal.c)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(Year2023Day02 PRIVATE advent)