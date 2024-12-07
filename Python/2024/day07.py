"""
--- Day 7: Bridge Repair ---
"""

from itertools import product
from operator import add, mul
from aocd import get_data


def concat(a, b):
    """a || b = ab, ex. 12 || 345 = 12345"""
    return int(str(a) + str(b))


data = get_data(day=7, year=2024).splitlines()


def chk(ll, rr, ops):
    """Can we find a valid expression l = ops(r)?"""
    num = len(rr) - 1

    for op in product(ops, repeat=num):
        res = rr[0]
        for n, o in zip(rr[1:], op):
            res = o(res, n)

        if res == ll:
            return True

    return False


ONE, TWO = 0, 0
for ln in data:
    # get parts
    l, *r = map(int, ln.replace(":", "").split())

    # Use add, mul (P1)
    if chk(l, r, [add, mul]):
        ONE += l
        TWO += l
    # Use add, mul, concat (P2)
    elif chk(l, r, [add, mul, concat]):
        TWO += l


print("ONE:", ONE)
print("TWO:", TWO)
