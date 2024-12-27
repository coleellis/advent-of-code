"""
--- Day 25: Code Chronicle ---
"""

from itertools import combinations
from aocd import get_data

data = get_data(day=25, year=2024).split("\n\n")

ONE = sum(
    not any(x == y == "#" for x, y in zip(a, b)) for a, b in combinations(data, 2)
)
print("ONE:", ONE)
