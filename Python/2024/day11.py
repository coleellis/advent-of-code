"""
--- Day 11: Plutonian Pebbles ---
"""

from functools import cache
from aocd import get_data

data = get_data(day=11, year=2024)


@cache
def blink(r, i, end):
    """Find number of stones after n runs"""
    if i == end:
        return 1

    if r == 0:
        return blink(1, i + 1, end)
    elif len(str(r)) % 2 == 0:
        return blink(int(str(r)[: len(str(r)) // 2]), i + 1, end) + blink(
            int(str(r)[len(str(r)) // 2 :]), i + 1, end
        )
    else:
        return blink(r * 2024, i + 1, end)


def run(end):
    """Run the code"""
    nums = [int(x) for x in data.strip().split(" ")]
    return sum(blink(r, 0, end) for r in nums)


print("ONE:", run(25))
print("TWO:", run(75))
