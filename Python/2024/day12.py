"""
--- Day 12: Garden Groups ---
"""

from collections import deque
from aocd import get_data

dirs = [(-1, 0, "L"), (0, -1, "TU"), (1, 0, "R"), (0, 1, "D")]


def flood(grid, x, y):
    """Flood Algorithm to find all connected letters"""
    a, p = 0, 0
    v = {(x, y)}

    q = deque()
    q.append((x, y))

    while q:
        x, y = q.popleft()
        a += 1

        # Shoelace
        p += sum(
            (
                x == 0 or grid[y][x - 1] != grid[y][x],
                y == 0 or grid[y - 1][x] != grid[y][x],
                x + 1 == len(grid[y]) or grid[y][x + 1] != grid[y][x],
                y + 1 == len(grid) or grid[y + 1][x] != grid[y][x],
            )
        )

        # Where to go next
        for nx, ny in ((x - 1, y), (x, y - 1), (x + 1, y), (x, y + 1)):
            if not (0 <= nx < len(grid[0]) and 0 <= ny < len(grid)):
                continue
            if grid[ny][nx] != grid[y][x]:
                continue
            if (nx, ny) in v:
                continue

            v.add((nx, ny))
            q.append((nx, ny))

    return a, p, v


def sides(region):
    """Count sides of a shape by its vertices"""
    f = set()
    s = 0

    for x, y in sorted(region, key=lambda x: tuple(reversed(x))):
        for dx, dy, d in dirs:
            ax, ay = x + dx, y + dy
            if (ax, ay) not in region:
                dx, dy = int(ax == x), int(ay == y)
                if (x - dx, y - dy, d) not in f and (
                    x - dx,
                    y - dy,
                    d,
                ) not in f:
                    s += 1
                f.add((x, y, d))

    return s


data = get_data(day=12, year=2024)
grid = [x.strip() for x in data.splitlines()]

vis = set()
ONE, TWO = 0, 0

for y, row in enumerate(grid):
    for x in range(len(row)):
        if (x, y) in vis:
            continue

        # Get flood path
        a, p, r = flood(grid, x, y)
        ONE += a * p
        TWO += a * sides(r)
        vis |= r


print(f"ONE: {ONE}")
print(f"TWO: {TWO}")
