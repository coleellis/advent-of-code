"""
--- Day 21: Step Counter ---
"""

from collections import deque
import numpy as np
from aocd import get_data

stream = get_data(day=21, year=2023).splitlines()
DIRS = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def valid(mm, row, col):
    """Check if a row, col coordinate is valid"""
    return 0 <= row < len(mm) and 0 <= col < len(mm[0]) and mm[row][col] != "#"


def reach(mm, sp, ss):
    """Number of plots reachable in ss steps"""
    v = set()
    q = deque([(sp, 0)])
    while q:
        (row, col), steps = q.popleft()
        if steps > ss:
            continue
        for dr, dc in DIRS:
            nx, ny = row + dr, col + dc
            if valid(mm, nx, ny) and (nx, ny) not in v:
                v.add((nx, ny))
                q.append(((nx, ny), steps + 1))
    return len([(row, col) for row, col in v if (row + col) % 2 == ss % 2])


def reach_around(ss):
    """Approximate number of plots reachable in ss steps for an infinite grid"""
    exp = [
        [gg[i % len(gg)][j % len(gg[0])] for j in range(5 * len(gg[0]))]
        for i in range(5 * len(gg))
    ]
    sp = len(exp) // 2, len(exp[0]) // 2
    yy = [reach(exp, sp, s) for s in [65, 65 + 131, 65 + 131 * 2]]
    xx = np.array([0, 1, 2])
    t = (ss - 65) // 131
    c = np.polyfit(xx, yy, 2)
    return np.round(np.polyval(c, t), 0).astype(int)


gg = [list(row) for row in stream]
pp = len(gg) // 2, len(gg[0]) // 2

print("Part 1:", reach(gg, pp, 64))
print("Part 2:", reach_around(26501365))
