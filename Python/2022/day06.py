"""
--- Day 6: Tuning Trouble ---
"""
from collections import Counter
from aocd import get_data


def solve(s, l):
    """Returns the first index of a substring of length l with all unique characters"""
    i = 0
    while len(Counter(s[i : i + l]).keys()) != l:
        i += 1
    return i + l


lines = get_data(day=6, year=2022)
print("Part 1:", solve(lines, 4))
print("Part 2:", solve(lines, 14))
