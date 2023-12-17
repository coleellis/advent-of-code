"""
--- Day 6: Probably a Fire Hazard ---
"""
from aocd import get_data

stream = get_data(day=6, year=2015).splitlines()
grid = [[0 for _ in range(1000)] for _ in range(1000)]

for line in stream:
    line = line.split(" ")
    if line[0] == "toggle":
        x1, y1 = [int(x) for x in line[1].split(",")]
        x2, y2 = [int(y) for y in line[3].split(",")]
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                grid[x][y] = not grid[x][y]
    elif line[0] == "turn":
        x1, y1 = [int(x) for x in line[2].split(",")]
        x2, y2 = [int(y) for y in line[4].split(",")]
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                grid[x][y] = line[1] == "on"
    else:
        raise ValueError("Invalid input")
one = sum(sum(x) for x in grid)

grid = [[0 for _ in range(1000)] for _ in range(1000)]

for line in stream:
    line = line.split(" ")
    if line[0] == "toggle":
        x1, y1 = [int(x) for x in line[1].split(",")]
        x2, y2 = [int(y) for y in line[3].split(",")]
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                grid[x][y] += 2
    elif line[0] == "turn":
        x1, y1 = [int(x) for x in line[2].split(",")]
        x2, y2 = [int(y) for y in line[4].split(",")]
        for x in range(x1, x2 + 1):
            for y in range(y1, y2 + 1):
                grid[x][y] += 1 if line[1] == "on" else -1
                grid[x][y] = max(grid[x][y], 0)
    else:
        raise ValueError("Invalid input")
two = sum([sum(x) for x in grid])

print("Part 1:", one)
print("Part 2:", two)
