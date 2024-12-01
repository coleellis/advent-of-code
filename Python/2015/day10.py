"""
--- Day 10: Elves Look, Elves Say ---
"""

import itertools
from aocd import get_data

stream = get_data(day=10, year=2015).strip()


def look_and_say(s, n):
    """Look and say n times"""
    for _ in range(n):
        s = "".join(str(len(list(g))) + k for k, g in itertools.groupby(s))
    return s


print("Part 1:", len(look_and_say(stream, 40)))
print("Part 2:", len(look_and_say(stream, 50)))
