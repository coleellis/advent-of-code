"""
--- Day 17: Chronospatial Computer ---
"""

import re
from aocd import get_data

data = get_data(day=17, year=2024)
a, b, c, *prog = map(int, re.findall(r"\d+", data))


def comp(a, b, c, i=0, R=[]):
    """Run evaluation per directions"""
    while i in range(len(prog)):
        dd = {0: 0, 1: 1, 2: 2, 3: 3, 4: a, 5: b, 6: c}

        match prog[i : i + 2]:
            case 0, op:
                a = a >> dd[op]
            case 1, op:
                b = b ^ op
            case 2, op:
                b = 7 & dd[op]
            case 3, op:
                i = op - 2 if a else i
            case 4, _:
                b = b ^ c
            case 5, op:
                R = R + [dd[op] & 7]
            case 6, op:
                b = a >> dd[op]
            case 7, op:
                c = a >> dd[op]
        i += 2
    return R


# P1
print("ONE:", *comp(a, b, c), sep=",")


def find(_a, i):
    """Find smallest value"""
    if comp(_a, b, c) == prog:
        print("TWO:", _a)
        exit()  # Stop at the smallest one
    if comp(_a, b, c) == prog[-i:] or not i:
        for n in range(8):
            find(8 * _a + n, i + 1)


# P2
find(0, 0)
