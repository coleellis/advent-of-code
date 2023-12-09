"""
--- Day 13: Distress Signal ---
"""
from itertools import zip_longest
from aocd import get_data

stream = get_data(day=13, year=2022)


def compare(left, right):
    """Returns whether left is less than right"""
    z = zip_longest(left, right, fillvalue=None)
    for p in z:
        l, r = p
        res = None

        if isinstance(l, int) and isinstance(r, int):
            if l < r:
                return True
            elif l > r:
                return False
        elif isinstance(l, list) and isinstance(r, list):
            res = compare(l, r)
        elif isinstance(l, int) and isinstance(r, list):
            res = compare([l], r)
        elif isinstance(l, list) and isinstance(r, int):
            res = compare(l, [r])

        elif l is None:
            return True
        elif r is None:
            return False
        if res is not None:
            return res


def one():
    """Returns the number of pairs where the first is less than the second"""
    n = 0
    s_pairs = [pair.split("\n") for pair in stream.split("\n\n")]
    pairs = list(map(lambda p: [eval(i) for i in p], s_pairs))
    for i, pair in enumerate(pairs, start=1):
        n += i if compare(pair[0], pair[1]) > 0 else 0
    return n


def two():
    """Finds [2] and [6] and returns their product"""
    pairs = [eval(l.strip()) for l in stream.split("\n") if l and l != "\n"]
    st = 1
    ss = 2
    for p in pairs:
        st += 1 if compare(p, [[2]]) else 0
        ss += 1 if compare(p, [[6]]) else 0
    return st * ss


F = one()
S = two()

print("Part 1:", F)
print("Part 2:", S)
