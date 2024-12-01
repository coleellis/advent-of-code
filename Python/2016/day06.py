"""
--- Day 6: Signals and Noise ---
"""

from aocd import get_data

stream = get_data(year=2016, day=6).splitlines()

gg = []
for i in range(len(stream[0])):
    gg.append({})
    for l in stream:
        gg[i][l[i]] = gg[i].get(l[i], 0) + 1

ONE, TWO = "", ""
for g in gg:
    ONE += max(g, key=g.get)
    TWO += min(g, key=g.get)
print("Part 1:", ONE)
print("Part 2:", TWO)
