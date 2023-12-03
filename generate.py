import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-y", "--year", type=int, default=2023, help="Advent Calendar Year")
parser.add_argument("-d", "--day", type=int, default=25, help="Advent Calendar Day")
args = parser.parse_args()

year = args.year
day = args.day

# attempt to make the year directory
import os

try:
    os.mkdir(f"{year}")
    # if we're here, we made a new directory
    with open("CMakeLists.txt", "a") as f:
        f.write(f"add_subdirectory({year})\n")
except FileExistsError:
    pass
os.chdir(f"{year}")

# attempt to make the day directory
try:
    os.mkdir(f"day-{int(day):02d}")
    # if we're here, we made a new directory
    with open("CMakeLists.txt", "a") as f:
        f.write(f"add_subdirectory(day-{int(day):02d})\n")
except FileExistsError:
    pass
os.chdir(f"day-{int(day):02d}")

# generate the day's files
with open("CMakeLists.txt", "w") as f:
    f.write(f"add_executable(Year{int(year)}Day{int(day):02d} solve.c)\n")
    f.write("configure_file(input.txt input.txt COPYONLY)\n")
    f.write(f"target_link_libraries(Year{int(year)}Day{int(day):02d} PRIVATE advent)\n")

with open("solve.c", "w") as f:
    f.write("#include <stdio.h>\n")
    f.write("#include <stdlib.h>\n")
    f.write("#include <string.h>\n")
    f.write("#include <ctype.h>\n")
    f.write("#include <advent.h>\n")
    f.write("\n")
    f.write("int one(FILE *fp)\n")
    f.write("{\n")
    f.write("\treturn 0;\n")
    f.write("}\n")
    f.write("\n")
    f.write("int two(FILE *fp)\n")
    f.write("{\n")
    f.write("\treturn 0;\n")
    f.write("}\n")
    f.write("\n")
    f.write("int main()\n")
    f.write("{\n")
    f.write('\tFILE *fp = fopen("input.txt", "r");\n')
    f.write("\tif (!fp)\n")
    f.write("\t{\n")
    f.write('\t\tprintf("Bad file read\\n");\n')
    f.write("\t\texit(EXIT_FAILURE);\n")
    f.write("\t}\n")
    f.write("\n")
    f.write('\tprintf("ONE: %d\\n", one(fp));\n')
    f.write("\tfseek(fp, 0, 0);\n")
    f.write('\tprintf("TWO: %d\\n", two(fp));\n')
    f.write("\n")
    f.write("\tfclose(fp);\n")
    f.write("\treturn 0;\n")
    f.write("}\n")

os.system("touch input.txt")
