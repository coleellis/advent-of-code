"""
--- Day 8: Resonant Collinearity ---
"""

from aocd import get_data

data = get_data(day=8, year=2024)

# Make the grid
grid = [list(l.strip()) for l in data.splitlines()]
r, c = len(grid), len(grid[0])

# Track the nodes
n = {}
for i in range(r):
    for j in range(c):
        if grid[i][j] != ".":
            if grid[i][j] in n:
                n[grid[i][j]].append((i, j))
            else:
                n[grid[i][j]] = [(i, j)]

# Sets of antinodes
an1, an2 = set(), set()


def one(a, b):
    """Solver for Part 1"""
    x1, y1 = a
    x2, y2 = b
    # New Location
    nx = x2 + (x2 - x1)
    ny = y2 + (y2 - y1)
    # Validate bounds
    if 0 <= nx < r and 0 <= ny < c:
        an1.add((nx, ny))


def two(a, b):
    """Solver for Part 2"""
    x1, y1 = a
    x2, y2 = b
    # New location
    nx = x2 + (x2 - x1)
    ny = y2 + (y2 - y1)
    # Add b
    an2.add((x2, y2))
    # Keep looking around
    while 0 <= nx < r and 0 <= ny < c:
        an2.add((nx, ny))
        nx += x2 - x1
        ny += y2 - y1


for k, v in n.items():
    for i, n1 in enumerate(v):
        for j in range(i):
            n2 = v[j]
            # Part 1
            one(n1, n2)
            one(n2, n1)
            # Part 2
            two(n1, n2)
            two(n2, n1)

print("ONE:", len(an1))
print("TWO:", len(an2))
