"""
--- Day 10: Pipe Maze ---
"""
from aocd import get_data

stream = get_data(day=10, year=2023).split("\n")

grid = [[i for i in x] for x in stream]
grid = {(x, y): c for y, r in enumerate(grid) for x, c in enumerate(r)}

dirs = {
    "|": [(0, 1), (0, -1)],
    "-": [(1, 0), (-1, 0)],
    "L": [(0, -1), (1, 0)],
    "J": [(0, -1), (-1, 0)],
    "7": [(0, 1), (-1, 0)],
    "F": [(0, 1), (1, 0)],
}


i = 1
dist = {}
sx, sy = list(k for k, v in grid.items() if v == "S")[0]
xx, yy = sx, sy

# base case, move away from S
for x, y in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
    if grid[(xx + x, yy + y)] != ".":
        xx, yy = xx + x, yy + y
        break
# run until we find S again
while True:
    dist[(xx, yy)] = i
    i += 1
    for x, y in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        z = grid[(xx, yy)]
        RUN = True
        if grid[(xx, yy)] in dirs:
            for d in dirs[grid[(xx, yy)]]:
                if (xx + d[0], yy + d[1]) not in dist:
                    xx, yy = xx + d[0], yy + d[1]
                    RUN = False
                    break
        if not RUN:
            break
    if grid[(xx, yy)] == "S":
        break
print("Part 1:", i // 2)

dist[(sx, sy)] = 0
x_min = min(x for x, _ in grid.keys())
x_max = max(x for x, _ in grid.keys())
y_min = min(y for _, y in grid.keys())
y_max = max(y for _, y in grid.keys())

TWO = 0
for y in range(y_min, y_max + 1):
    WINDS = 0
    for x in range(x_min, x_max + 1):
        if (x, y) in dist and (x, y + 1) in dist:
            if dist[(x, y + 1)] == (dist[(x, y)] + 1) % i:
                WINDS += 1
            elif (dist[(x, y + 1)] + 1) % i == dist[(x, y)]:
                WINDS -= 1
        TWO += (x, y) not in dist and WINDS != 0
print("Part 2:", TWO)
