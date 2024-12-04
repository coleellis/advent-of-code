"""
--- Day 14: Parabolic Reflector Dish ---
"""

from aocd import get_data
import numpy as np

stream = get_data(day=14, year=2023).splitlines()
data = np.array([list(x) for x in stream])


def shake(arr):
    """Move all the O's as North as possible"""
    bad = True
    while bad:
        bad = False
        for y, l in enumerate(arr[:-1]):
            for x, s in enumerate(l):
                if s == "." and arr[y + 1][x] == "O":
                    l[x] = "O"
                    arr[y + 1][x] = "."
                    bad = True
    return arr


def cycle(arr):
    """N/W/S/E Shake"""
    for _ in range(4):
        arr = shake(arr)
        arr = np.rot90(arr, k=1, axes=(1, 0))
    return arr


def load(arr):
    """Compute load of the array"""
    arr = np.rot90(arr, axes=(1, 0))
    return sum(sum(i + 1 for i, c in enumerate(l) if c == "O") for l in arr)


nd = data.copy()
print("Part 1:", load(shake(data)))

hh = []
T = 0
while True:
    # Have we seen this iteration before?
    lst = ["".join(l) for l in list(nd)]
    h = hash(tuple(["".join(l) for l in list(nd)]))
    if h in hh and not T:
        ss = hh.index(h)
        ll = len(hh) - ss
        T = (1000000000 - ss) % ll + ss + ll

    if T and len(hh) == T:
        break

    hh.append(h)
    nd = cycle(nd)
print("Part 2:", load(nd))
