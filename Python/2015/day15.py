"""
--- Day 15: Science for Hungry People ---
"""

import re
from itertools import combinations
from aocd import get_data

stream = get_data(year=2015, day=15).splitlines()

dd = {}
for l in stream:
    nn = re.findall(r"-?\d+", l)
    dd[l.split()[0]] = tuple(map(int, nn))


def partitions(n, k):
    """Generate partitions of n items into k buckets"""
    for c in combinations(range(n + k - 1), k - 1):
        yield [b - a - 1 for a, b in zip((-1,) + c, c + (n + k - 1,))]


def score(mix):
    """Get score for a given mix"""
    ss = 1
    for cc in zip(*(v[:-1] for v in dd.values())):
        s = sum(c * m for c, m in zip(cc, mix))
        ss *= 0 if s < 0 else s
    return ss


def calories(mix):
    """Get calories for a given mix"""
    return sum(c * m for c, m in zip((v[-1] for v in dd.values()), mix))


pp = list(partitions(100, len(dd)))
print("Part 1:", max(score(p) for p in pp))
print("Part 2:", max(score(p) for p in pp if calories(p) == 500))
