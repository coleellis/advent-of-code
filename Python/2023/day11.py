"""
--- Day 11: Cosmic Expansion ---
"""
import itertools
from aocd import get_data

stream = get_data(day=11, year=2023).split("\n")


def shortest_path(pair):
    """Get the shortest traveling path between two points"""
    f, s = pair
    return abs(s[0] - f[0]) + abs(s[1] - f[1])


def solve(dup=1):
    """Solve the cosmic expansion problem for some duplicate size"""
    # get the original points
    p = set()
    for y, line in enumerate(stream):
        for x, c in enumerate(line):
            if c == "#":
                p.add((x, y))

    # get the rows that are empty
    rows = []
    for i, x in enumerate(stream):
        if x.find("#") == -1:
            rows.append(i)
    # do the same for the columns
    t = list(zip(*stream))
    cols = []
    for i, x in enumerate(t):
        if not any("#" in e for e in x):
            cols.append(i)

    n = set()
    for x, y in p:
        r_inc = sum(1 for r in rows if r < y) * dup
        c_inc = sum(1 for c in cols if c < x) * dup
        n.add((x + c_inc, y + r_inc))

    zz = 0
    for pair in itertools.combinations(n, 2):
        c = shortest_path(pair)
        zz += c
    return zz


one = solve(1)
print("Part 1:", one)
two = solve(999999)
print("Part 2:", two)
