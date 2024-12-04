"""
--- Day 2: Red-Nosed Reports ---
"""

from aocd import get_data

data = get_data(day=2, year=2024).splitlines()


def safe(i):
    """Checks whether row is safe."""
    sf = True
    flag = True
    inc = True
    for a, b in zip(i, i[1:]):
        if flag:
            inc = b - a > 0
        if (inc and a > b) or (not inc and a < b):
            sf = False
            break
        if abs(b - a) < 1 or abs(b - a) > 3:
            sf = False
            break
        flag = False
    return sf


ONE = 0
for ln in data:
    r = [int(x) for x in ln.split(" ")]
    if safe(r):
        ONE += 1
print("ONE:", ONE)

TWO = 0
for ln in data:
    r = [int(x) for x in ln.split(" ")]
    for idx in range(len(r)):
        nr = r[:idx] + r[idx + 1 :]
        if safe(nr):
            TWO += 1
            break
print("TWO:", TWO)
