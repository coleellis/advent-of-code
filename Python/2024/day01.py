"""
--- Day 01: Historian Hysteria ---
"""

from aocd import get_data

data = get_data(day=1, year=2024).splitlines()

left = []
right = []
for l in data:
    s = l.split(" ")
    left.append(int(s[0]))
    right.append(int(s[-1]))


first = sorted(left)
second = sorted(right)
ONE = sum(abs(b - a) for a, b in zip(first, second))
print("ONE:", ONE)

TWO = sum(x * right.count(x) for x in left)
print("TWO:", TWO)
