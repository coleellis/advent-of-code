"""
--- Day 9: Mirage Maintenance ---
"""

from aocd import get_data

print(get_data(day=9, year=2023))

data = [x.strip().split() for x in get_data(day=9, year=2023).split("\n")]
data = [[int(x) for x in line] for line in data]

ONE = 0
TWO = 0
for line in data:
    # make a list of sequential differences
    d = line
    p = [d]
    while any(d):
        d = [d[i + 1] - d[i] for i in range(len(d) - 1)]
        p.append(d)

    # backtrack, adding predicted value to each list
    p.reverse()
    for i, a in enumerate(p):
        if i != 0:
            a.append(p[i - 1][-1] + a[-1])
            a.insert(0, a[0] - p[i - 1][0])

    # target is the last value in the last list
    ONE += p[-1][-1]
    TWO += p[-1][0]
print(f"Part 1: {ONE}")
print(f"Part 2: {TWO}")
