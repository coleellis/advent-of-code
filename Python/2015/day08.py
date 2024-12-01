"""
--- Day 8: Matchsticks ---
"""

from aocd import get_data

stream = get_data(day=8, year=2015).splitlines()

ONE = 0
for l in stream:
    ONE += len(l) - len(eval(l))

TWO = 0
for l in stream:
    TWO += 2 + l.count('"') + l.count("\\")

print("Part 1:", ONE)
print("Part 2:", TWO)
