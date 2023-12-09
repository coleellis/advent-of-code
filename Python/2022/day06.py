from aocd import get_data
from collections import Counter


def solve(s, l):
    i = 0
    while len(Counter(s[i : i + l]).keys()) != l:
        i += 1
    return i + l


lines = get_data(day=6, year=2022)
print("Part 1:", solve(lines, 4))
print("Part 2:", solve(lines, 14))
