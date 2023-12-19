"""
--- Day 3: Squares With Three Sides ---
"""
import re
from aocd import get_data

stream = get_data(year=2016, day=3).splitlines()


def v(t):
    """Check if a triangle is valid"""
    return (t[0] + t[1] > t[2]) and (t[1] + t[2] > t[0]) and (t[2] + t[0] > t[1])


ONE = 0
for l in stream:
    nn = list(map(int, re.findall(r"\d+", l)))
    ONE += v(nn)
print("Part 1:", ONE)

TWO = 0
for i in range(0, len(stream), 3):
    nn = []
    for j in range(3):
        nn.append(list(map(int, re.findall(r"\d+", stream[i + j]))))
    nn = list(zip(*nn))
    for j in range(3):
        TWO += v(nn[j])
print("Part 2:", TWO)
