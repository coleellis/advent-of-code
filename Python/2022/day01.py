"""
--- Day 1: Calorie Counting ---
"""
from aocd import get_data

d = [z.split() for z in get_data(day=1, year=2022).split("\n\n")]
n = [sum([int(x) for x in z]) for z in d]
print("Part 1:", max(n))

n = sorted(n, reverse=True)
print("Part 2:", sum(n[:3]))
