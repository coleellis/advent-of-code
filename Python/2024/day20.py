"""
--- Day 20: Race Condition ---
"""

from aocd import get_data

data = get_data(day=20, year=2024)


def cheat(track, cap):
    """Find cheats across the track"""
    for t1, (x1, y1) in enumerate(track):
        for t2 in range(t1 + 3, len(track)):
            x2, y2 = track[t2]
            dist = abs(x2 - x1) + abs(y2 - y1)
            if dist <= cap and t2 - t1 > dist:
                yield t2 - t1 - dist


grid = [line.strip() for line in data.splitlines()]
x, y = next((x, y) for y, r in enumerate(grid) for x, c in enumerate(r) if c == "S")
t = [None, (x, y)]

while grid[y][x] != "E":
    x, y = next(
        n
        for n in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1))
        if n != t[-2] and grid[n[1]][n[0]] != "#"
    )
    t.append((x, y))

print("ONE:", sum(s >= 100 for s in cheat(t[1:], 2)))
print("TWO:", sum(s >= 100 for s in cheat(t[1:], 20)))
