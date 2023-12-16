"""
--- Day 13: Point of Incidence ---
"""
from aocd import get_data
import numpy as np


def symmetry(arr, margin):
    """Find line of symmetry in 2D array"""
    i = 1
    while i < len(arr):
        lhs = arr[:i]
        rhs = arr[i:]
        if len(lhs) > len(rhs):
            lhs = lhs[len(lhs) - len(rhs) :]
        elif len(rhs) > len(lhs):
            rhs = rhs[: len(lhs)]
        rhs = np.flip(rhs, axis=0)
        if np.count_nonzero(lhs != rhs) == margin:
            return i
        i += 1
    return False


stream = get_data(day=13, year=2023).split("\n\n")
stream = [line.splitlines() for line in stream]

for l in stream:
    print(l)


def iterate(margin):
    """Iterate across all puzzles and get symmetry score"""
    r = 0
    for dis in stream:
        data = np.array([list(l) for l in dis])
        transpose = data.T

        val = symmetry(transpose, margin)
        if not val:
            val = 100 * symmetry(data, margin)
        r += val
    return r


print("Part 1:", iterate(0))
print("Part 2:", iterate(1))
