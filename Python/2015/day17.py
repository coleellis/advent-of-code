"""
--- Day 17: No Such Thing as Too Much ---
"""

from itertools import combinations
from aocd import get_data

stream = get_data(day=17, year=2015).splitlines()
data = [int(line) for line in stream]

ac = [
    c for i in range(1, len(data) + 1) for c in combinations(data, i) if sum(c) == 150
]
print("Part 1:", len(ac))
print("Part 2:", sum(len(c) == min(len(c) for c in ac) for c in ac))
