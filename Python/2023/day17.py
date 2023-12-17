"""
--- Day 17: Clumsy Crucible ---
"""
from heapq import heappop, heappush
from aocd import get_data

stream = get_data(day=17, year=2023).strip().splitlines()

data = [[int(y) for y in x] for x in stream]
DIRS = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def in_range(pp, arr):
    """in range"""
    return pp[0] in range(len(arr)) and pp[1] in range(len(arr[0]))


def dijkstra(t_min, t_max):
    """Run dijkstra's algorithm"""
    q = [(0, 0, 0, -1)]
    ss = set()
    cc = {}
    while q:
        c, x, y, dd = heappop(q)
        if x == len(data) - 1 and y == len(data[0]) - 1:
            return c
        if (x, y, dd) in ss:
            continue
        ss.add((x, y, dd))
        for d in range(4):
            ci = 0
            if d == dd or (d + 2) % 4 == dd:
                continue
            for dis in range(1, t_max + 1):
                xx = x + DIRS[d][0] * dis
                yy = y + DIRS[d][1] * dis
                if in_range((xx, yy), data):
                    ci += data[xx][yy]
                    if dis < t_min:
                        continue
                    nc = c + ci
                    if cc.get((xx, yy, d), 1e100) <= nc:
                        continue
                    cc[(xx, yy, d)] = nc
                    heappush(q, (nc, xx, yy, d))


print("Part 1:", dijkstra(1, 3))
print("Part 2:", dijkstra(4, 10))
