"""
--- Day 2: I Was Told There Would Be No Math ---
"""

from aocd import get_data

stream = get_data(day=2, year=2015).splitlines()
data = [[int(y) for y in x.split("x")] for x in stream]

ONE = 0
for p in data:
    x = p[0] * p[1]
    y = p[1] * p[2]
    z = p[2] * p[0]
    ONE += 2 * (x + y + z) + min(x, y, z)

TWO = 0
for p in data:
    v = p[0] * p[1] * p[2]
    l = 2 * min(p[0] + p[1], p[1] + p[2], p[2] + p[0])
    TWO += v + l

print("Part 1:", ONE)
print("Part 2:", TWO)
