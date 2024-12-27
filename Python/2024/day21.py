"""
--- Day 21: Keypad Conundrum ---
"""

from functools import cache
from aocd import get_data

data = get_data(day=21, year=2024)


def path(ss):
    """Get the path"""
    (y1, x1), (y2, x2) = [divmod("789456123_0A<v>".find(t), 3) for t in ss]
    s = ">" * (x2 - x1) + "v" * (y2 - y1) + "0" * (y1 - y2) + "<" * (x1 - x2)
    return s if (3, 0) in [(y1, x2), (y2, x1)] else s[::-1]


@cache
def length(s, d):
    """Cached length of robot path"""
    if d < 0:
        return len(s) + 1
    return sum(length(path(ss), d - 1) for ss in zip("A" + s, s + "A"))


def solve(r):
    """Solver for r robots"""
    return sum(int(S[:3]) * length(S[:3], r) for S in data.splitlines())


print("ONE:", solve(2))
print("TWO:", solve(25))
