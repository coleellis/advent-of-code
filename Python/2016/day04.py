"""
--- Day 4: Security Through Obscurity ---
"""
import re
from aocd import get_data

stream = get_data(year=2016, day=4).splitlines()

ONE = 0
for l in stream:
    n, c, s = re.match(r"(.*)-(\d+)\[(.*)]", l).groups()
    n = sorted(n.replace("-", ""), key=lambda x: (-n.count(x), x))
    n = list(dict.fromkeys(n))
    if "".join(n[:5]) == s:
        ONE += int(c)
print("Part 1:", ONE)


def shift(nn, cc):
    """Shift a character by nn"""
    if cc == "-" and nn % 2 == 1:
        return " "
    if cc == " " and nn % 2 == 1:
        return "-"
    return chr((ord(cc) - ord("a") + nn) % 26 + ord("a"))


TWO = 0
for l in stream:
    n, c, s = re.match(r"(.*)-(\d+)\[(.*)]", l).groups()
    n = "".join(map(lambda x: shift(int(c), x), n))
    if "north" in n:
        TWO = c
print("Part 2:", TWO)
