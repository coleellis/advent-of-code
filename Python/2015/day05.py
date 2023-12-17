"""
--- Day 5: Doesn't He Have Intern-Elves For This? ---
"""
import re
from aocd import get_data

stream = get_data(day=5, year=2015).splitlines()

ONE = 0
for line in stream:
    if (
        re.search(r"(.)\1", line)
        and re.search(r"([aeiou].*){3}", line)
        and not re.search(r"ab|cd|pq|xy", line)
    ):
        ONE += 1

TWO = 0
for line in stream:
    if re.search(r"(..).*\1", line) and re.search(r"(.).\1", line):
        TWO += 1

print("Part 1:", ONE)
print("Part 2:", TWO)
