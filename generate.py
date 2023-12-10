"""
Generate the files for a new day
"""

import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument("-y", "--year", type=int, default=2023, help="Advent Calendar Year")
parser.add_argument("-d", "--day", type=int, default=25, help="Advent Calendar Day")
args = parser.parse_args()

year = args.year
day = args.day


def c_write():
    """
    Generate the C files for the day
    """
    os.chdir("C")
    try:
        os.mkdir(f"{year}")
        # if we're here, we made a new directory
        with open("CMakeLists.txt", "a", encoding="utf-8") as f:
            f.write(f"add_subdirectory({year})\n")
    except FileExistsError:
        pass
    os.chdir(f"{year}")

    ay = f"ay{int(day):02d}"

    # generate the day's files
    with open("CMakeLists.txt", "a", encoding="utf-8") as f:
        f.write(f"\n\n# day {int(day)}\n")
        f.write(f"add_executable({int(year)}-D{ay} d{ay}.c)\n")
        f.write(
            f"configure_file(${{IN_DIR}}/d{ay}.txt ${{OUT_DIR}}/d{ay}.txt COPYONLY)\n"
        )
        f.write(f"target_link_libraries({int(year)}-D{ay} PRIVATE advent)")

    filename = f"d{ay}.c"

    with open(filename, "w", encoding="utf-8") as f:
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
        f.write(f'\tFILE *fp = fopen("d{ay}.txt", "r");\n')
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

    os.chdir(f"../_input/{int(year)}")
    os.system(f"touch d{ay}.txt")
    os.chdir("../../..")


def py_write():
    """
    Generate the Python files for the day
    """
    os.chdir("Python")
    try:
        os.mkdir(f"{year}")
    except FileExistsError:
        pass

    os.chdir(f"{year}")

    filename = f"day{int(day):02d}.py"
    text = f"_input/{year}/day{int(day):02d}.txt"
    with open(filename, "w", encoding="utf-8") as f:
        f.write("from aocd import get_data, submit\n\n")
        f.write(f'# stream = get_data(day={int(day)}, year={year}).split("\\n")\n')
        f.write('stream = open("test.txt").read().split("\\n")\n\n')
        f.write("one = 0\n")
        f.write("two = 0\n\n")
        f.write('print("Part 1:", one)\n')
        f.write(f'# submit(one, part="a", day={int(day)}, year={year})\n')
        f.write('print("Part 2:", two)\n')
        f.write(f'# submit(two, part="b", day={int(day)}, year={year})\n')

    os.chdir("../..")
    os.system(f"touch ./Python/{text}")


def hs_write():
    """
    Generate the Haskell files for the day
    """
    os.chdir("Haskell")
    try:
        os.mkdir(f"{year}")
    except FileExistsError:
        pass

    os.chdir(f"{year}")

    filename = f"day{int(day):02d}.hs"
    with open(filename, "w", encoding="utf-8") as f:
        f.write("module DayXX where\n")
        f.write("\n")
        f.write("one :: String -> Int\n")
        f.write("one = undefined\n")
        f.write("\n")
        f.write("two :: String -> Int\n")
        f.write("two = undefined\n")

    os.chdir("../..")


# call our handless
c_write()
py_write()
hs_write()
