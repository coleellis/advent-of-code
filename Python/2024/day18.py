"""
--- Day 18: RAM Run ---
"""

from collections import deque
from aocd import get_data

data = get_data(day=18, year=2024)
grid = [tuple(map(int, x.strip().split(","))) for x in data.splitlines()]

DIRS = [(0, 1), (1, 0), (0, -1), (-1, 0)]
SIZE = 70
LEN = 1024


def bfs(_grid):
    """Standard BFS with deque"""
    q = deque()
    q.append((0, 0, 0))
    vis = set()

    while q:
        x, y, l = q.popleft()
        if (x, y) in vis:
            continue
        vis.add((x, y))

        if (x, y) == (SIZE, SIZE):
            return l
        for d in DIRS:
            if (
                0 <= x + d[0] <= SIZE
                and 0 <= y + d[1] <= SIZE
                and _grid[x + d[0]][y + d[1]] == "."
            ):
                q.append((x + d[0], y + d[1], l + 1))

    return None


# P1
mm = [["." for _ in range(SIZE + 1)] for _ in range(SIZE + 1)]
for i in range(LEN):
    c = grid[i]
    mm[c[1]][c[0]] = "#"
print("ONE:", bfs(mm))

# Reset the map
mm = [["." for _ in range(SIZE + 1)] for _ in range(SIZE + 1)]
for c in grid:
    mm[c[1]][c[0]] = "#"

# P2
for i in range(len(grid) - 1, 1024, -1):
    c = grid[i]
    mm[c[1]][c[0]] = "."
    TWO = bfs(mm)
    if TWO is not None:
        TWO = grid[i]
        break
print("TWO:", TWO)
