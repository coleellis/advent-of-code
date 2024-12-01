"""
--- Day 1: No Time for a Taxicab ---
"""

from aocd import get_data

stream = get_data(year=2016, day=1).split(", ")
DIRS = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}

x, y = 0, 0
DD = "N"
for l in stream:
    t, n = l[0], l[1:]
    n = int(n)
    if t == "L":
        ND = "NESW".index(DD) - 1
    else:
        ND = "NESW".index(DD) + 1
    DD = "NESW"[ND % 4]
    x, y = x + n * DIRS[DD][0], y + n * DIRS[DD][1]
print("Part 1:", abs(x) + abs(y))

x, y = 0, 0
DD = "N"
ss = set()
for l in stream:
    t, n = l[0], l[1:]
    n = int(n)
    if t == "L":
        ND = "NESW".index(DD) - 1
    else:
        ND = "NESW".index(DD) + 1
    DD = "NESW"[ND % 4]
    for i in range(n):
        x, y = x + DIRS[DD][0], y + DIRS[DD][1]
        if (x, y) in ss:
            break
        ss.add((x, y))
    else:
        continue
    break
print("Part 2:", abs(x) + abs(y))
