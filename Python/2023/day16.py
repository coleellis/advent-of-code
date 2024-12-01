"""
--- Day 16: The Floor Will Be Lava ---
"""

import sys
from aocd import get_data

sys.setrecursionlimit(1000000)

stream = get_data(day=16, year=2023).splitlines()
stream = [list(x) for x in stream]

DIRS = {"S": (0, 1), "N": (0, -1), "W": (-1, 0), "E": (1, 0)}
MIRRORS = {
    ".": {"E": ["E"], "N": ["N"], "S": ["S"], "W": ["W"]},
    "-": {"E": ["E"], "N": ["E", "W"], "S": ["E", "W"], "W": ["W"]},
    "|": {"E": ["N", "S"], "N": ["N"], "S": ["S"], "W": ["N", "S"]},
    "/": {"E": ["N"], "N": ["E"], "S": ["W"], "W": ["S"]},
    "\\": {"E": ["S"], "N": ["W"], "S": ["E"], "W": ["N"]},
}


def recurse(start):
    """Recurse until there are no possible moves left"""
    lst = set()

    def _recurse(x, y, dr):
        if (x, y, dr) in lst:
            return
        lst.add((x, y, dr))
        m = stream[y][x]
        for n in MIRRORS[m][dr]:
            dx, dy = DIRS[n]
            nx = x + dx
            ny = y + dy
            if nx in range(len(stream[0])) and ny in range(len(stream)):
                _recurse(nx, ny, n)

    _recurse(*start)
    return len(set((x, y) for x, y, _ in lst))


tests = []
for yy in range(len(stream)):
    tests.append((0, yy, "E"))
    tests.append((len(stream[0]) - 1, yy, "W"))
for xx in range(len(stream[0])):
    tests.append((xx, 0, "S"))
    tests.append((xx, len(stream) - 1, "N"))

print("Part 1:", recurse((0, 0, "E")))
print("Part 2:", max(recurse(test) for test in tests))
