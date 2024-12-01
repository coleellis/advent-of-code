"""
--- Day 2: Bathroom Security ---
"""

from aocd import get_data

stream = get_data(year=2016, day=2).splitlines()

DIRS = {"U": (0, -1), "R": (1, 0), "D": (0, 1), "L": (-1, 0)}
PAD = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

print("Part 1:", end=" ")
x, y = 1, 1
for l in stream:
    for c in l:
        dx, dy = DIRS[c]
        x = max(0, min(x + dx, 2))
        y = max(0, min(y + dy, 2))
    print(PAD[y][x], end="")
print()

PAD = [
    [None, None, 1, None, None],
    [None, 2, 3, 4, None],
    [5, 6, 7, 8, 9],
    [None, "A", "B", "C", None],
    [None, None, "D", None, None],
]

print("Part 2:", end=" ")
x, y = 0, 2
for l in stream:
    for c in l:
        dx, dy = DIRS[c]
        nx = max(0, min(x + dx, 4))
        ny = max(0, min(y + dy, 4))
        if PAD[ny][nx] is not None:
            x, y = nx, ny
    print(PAD[y][x], end="")
print()
