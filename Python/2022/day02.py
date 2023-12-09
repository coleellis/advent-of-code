"""
--- Day 2: Rock Paper Scissors ---
"""
from aocd import get_data

stream = get_data(day=14, year=2022)


def delta(a, b):
    """Returns game score between a and b"""
    return (ord(b) - ord(a) - 23) % 3


def react(a, b):
    """Returns move to achieve b given move a"""
    return (ord(b) - 64 + ord(a) - 64 - 25) % 3


d = [x.split() for x in stream.split("\n")]
ONE = 0
for x, y in d:
    s = delta(x, y)
    ONE += ord(y) - ord("W")
    ONE += 3 * s + 3 if s in (0, 1) else 0
print("Part 1:", ONE)

TWO = 0
for x, y in d:
    s = 3 if react(x, y) == 0 else react(x, y)
    TWO += s
    TWO += (ord(y) - ord("X")) * 3
print("Part 2:", TWO)
