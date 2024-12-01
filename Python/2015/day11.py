"""
--- Day 11: Corporate Policy ---
"""

import re
from aocd import get_data

stream = get_data(day=11, year=2015).strip()


def increment(s):
    """Increment a string by one letter"""
    if s[-1] == "z":
        return increment(s[:-1]) + "a"
    return s[:-1] + chr(ord(s[-1]) + 1)


def valid(s):
    """Check if a string is valid"""
    if "i" in s or "o" in s or "l" in s:
        return False
    if len(re.findall(r"(.)\1", s)) < 2:
        return False
    for i in range(len(s) - 2):
        if ord(s[i]) == ord(s[i + 1]) - 1 == ord(s[i + 2]) - 2:
            return True
    return False


while not valid(stream):
    stream = increment(stream)
print("Part 1:", stream)

stream = increment(stream)
while not valid(stream):
    stream = increment(stream)
print("Part 2:", stream)
