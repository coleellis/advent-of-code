"""
--- Day 3: Perfectly Spherical Houses in a Vacuum ---
"""

from aocd import get_data

stream = get_data(day=3, year=2015)

ss = set()
p = (0, 0)
for c in stream.strip():
    ss.add(p)
    if c == "^":
        p = (p[0], p[1] + 1)
    elif c == "v":
        p = (p[0], p[1] - 1)
    elif c == ">":
        p = (p[0] + 1, p[1])
    elif c == "<":
        p = (p[0] - 1, p[1])

print("Part 1:", len(ss))

ss = set()
p1 = (0, 0)
p2 = (0, 0)
for i, c in enumerate(stream.strip()):
    if i % 2 == 0:
        ss.add(p1)
        if c == "^":
            p1 = (p1[0], p1[1] + 1)
        elif c == "v":
            p1 = (p1[0], p1[1] - 1)
        elif c == ">":
            p1 = (p1[0] + 1, p1[1])
        elif c == "<":
            p1 = (p1[0] - 1, p1[1])
    else:
        ss.add(p2)
        if c == "^":
            p2 = (p2[0], p2[1] + 1)
        elif c == "v":
            p2 = (p2[0], p2[1] - 1)
        elif c == ">":
            p2 = (p2[0] + 1, p2[1])
        elif c == "<":
            p2 = (p2[0] - 1, p2[1])

print("Part 2:", len(ss))
