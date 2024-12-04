"""
--- Day 4: Ceres Search ---
"""

from aocd import get_data

data = get_data(day=4, year=2024)
search = []
for ln in data.splitlines():
    search.append(list(ln.strip()))
N = len(search)


def bounded(ii, jj):
    """Check whether coordinate is on the grid"""
    return 0 <= ii < N and 0 <= jj < N


ONE = 0
for i in range(N):
    for j in range(N):
        # Find start of string
        if search[i][j] != "X":
            continue

        # Walk the directions to find XMAS
        for di in [-1, 0, 1]:
            for dj in [-1, 0, 1]:
                # Don't count standing still
                if (di, dj) == (0, 0):
                    continue
                # Check bounds, then validate string via extension
                if (
                    bounded(i + 3 * di, j + 3 * dj)
                    and "".join(search[i + k * di][j + k * dj] for k in range(4))
                    == "XMAS"
                ):
                    ONE += 1
print("ONE:", ONE)

TWO = 0
for i in range(N):
    for j in range(N):
        # Check for middle (A)
        if search[i][j] != "A":
            continue

        # Make sure we're in bounds
        BOUND = True
        for k in [-1, 1]:
            for l in [-1, 1]:
                if not bounded(i + k, j + l):
                    BOUND = False
        if not BOUND:
            continue

        # Match characters
        if (search[i - 1][j - 1], search[i + 1][j + 1]) not in (("M", "S"), ("S", "M")):
            continue
        if (search[i + 1][j - 1], search[i - 1][j + 1]) not in (("M", "S"), ("S", "M")):
            continue

        TWO += 1
print("TWO:", TWO)
