"""
--- Day 14: Reindeer Olympics ---
"""
import re
from aocd import get_data

stream = get_data(day=14, year=2015).splitlines()
TT = 2503

dd = {}
for l in stream:
    n = re.findall(r"\d+", l)
    dd[l.split()[0]] = tuple(map(int, n))


def solve(rr, mt):
    """Find maximum distance per reindeer"""
    s, t, r = dd[rr]
    return (mt // (t + r)) * s * t + s * min(mt % (t + r), t)


print("Part 1:", max(solve(rr, TT) for rr in dd))

ss = {}
for d in dd:
    ss[d] = 0

for ti in range(1, TT + 1):
    m = {}
    for d in dd:
        m[d] = solve(d, ti)
    for d in dd:
        if m[d] == max(m.values()):
            ss[d] += 1
print("Part 2:", max(ss.values()))
