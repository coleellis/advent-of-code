"""
--- Day 6: Wait For It ---
"""
from functools import reduce
from aocd import get_data

data = get_data(day=6, year=2023).split("\n")
times = list(map(int, data[0].split(":")[1].strip().split()))
dists = list(map(int, data[1].split(":")[1].strip().split()))


def win(t, d):
    """Returns the number of possible paths"""
    return sum(1 for i in range(t) if i * (t - i) > d)


one = reduce(lambda x, y: x * y, map(win, times, dists))
print("ONE:", one)

TIME = int("".join(map(str, times)))
DIST = int("".join(map(str, dists)))

two = sum(1 for i in range(TIME) if i * (TIME - i) > DIST)
print("TWO:", two)
