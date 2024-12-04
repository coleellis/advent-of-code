"""
--- Day 14: Regolith Reservoir ---
"""

from aocd import get_data

stream = get_data(day=14, year=2022).splitlines()

data = [[[int(z) for z in y.split(",")] for y in x.split("->")] for x in stream]


def add(x, y):
    """Add sand/rock to set"""
    for dx in [0, -1, 1]:
        if (x + dx, y) not in bad and y < h + 2:
            return x + dx, y
    bad.add((x, y - 1))


def drop(i, m):
    """Drop sand until no more sand can fall"""
    while i := i + 1:
        x, y = 500, 0
        while xy := add(x, y + 1):
            x, y = xy[0], xy[1]
            if y == m:
                return i - 1
        if y == m:
            return i


# Add rocks to set
bad = set()
for p in data:
    for l in zip(p, p[1:]):
        for a in range(min(l)[0], max(l)[0] + 1):
            for b in range(min(l)[1], max(l)[1] + 1):
                bad.add((a, b))

# Add sand to set
h = max(p[1] for p in bad)
one = drop(0, h)
two = drop(one, 0)


print("Part 1:", one)
print("Part 2:", two)
