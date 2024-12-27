"""
--- Day 19: Linen Layout ---
"""

from functools import cache
from aocd import get_data

data = get_data(day=19, year=2024).split("\n\n")


@cache
def possible(design, towels):
    """If design is possible"""
    if not design:
        return 1
    return sum(
        possible(design[len(towel) :], towels)
        for towel in towels
        if design.startswith(towel)
    )


t = tuple([x.strip() for x in data[0].split(",")])
p = [possible(d, t) for d in data[1].splitlines()]

print("ONE:", sum(map(bool, p)))
print("TWO:", sum(p))
