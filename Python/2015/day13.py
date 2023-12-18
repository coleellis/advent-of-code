"""
--- Day 13: Knights of the Dinner Table ---
"""
from itertools import permutations
from aocd import get_data

stream = get_data(day=13, year=2015).splitlines()

hh = {}
for line in stream:
    line = line.replace(".", "").split()
    hh[(line[0], line[-1])] = int(line[3]) * (-1 if line[2] == "lose" else 1)


def solve(tp):
    """Find maximum happiness"""
    r = 0
    for t in permutations(tp):
        h = sum(
            [hh[(t[i], t[i + 1])] + hh[(t[i + 1], t[i])] for i in range(len(t) - 1)]
        )
        h += hh[(t[0], t[-1])] + hh[(t[-1], t[0])]
        r = max(r, h)
    return r


pp = tuple(list(set([x[0] for x in hh])))
print("Part 1:", solve(pp))

for p in pp:
    hh[("me", p)] = 0
    hh[(p, "me")] = 0
pp = tuple(list(set([x[0] for x in hh])))
print("Part 2:", solve(pp))
