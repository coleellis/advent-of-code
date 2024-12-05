"""
--- Day 5: Print Queue ---
"""

from collections import defaultdict
from aocd import get_data


def parse(d):
    """Parse data for rules and update list"""
    r, s = d.split("\n\n")

    # Get rule list
    rl = defaultdict(set)
    for x in r.split("\n"):
        if not x:
            continue
        b, a = map(int, x.split("|"))
        rl[b].add(a)

    # Get update list
    ul = []
    for x in s.split("\n"):
        if not x:
            continue
        ul.append([int(y) for y in x.split(",")])

    return rl, ul


def validate(u, rl):
    """Validate update under ruleset"""
    for i, x in enumerate(u):
        if x in rl:
            m = rl[x]
            rem = set(u[i + 1 :])
            for y in m:
                if y in u and y not in rem:
                    return False
    return True


def topsort(s, r):
    """Run topological sort"""
    n = len(s)
    res = []
    u = set()

    while len(res) < n:
        for x in s:
            if x in u:
                continue

            ok = True
            for b, a in r.items():
                if b not in s or b in u:
                    continue
                if x in a and b not in u:
                    ok = False
                    break

            if ok:
                res.append(x)
                u.add(x)
                break
    return res

# Get and parse data
data = get_data(day=5, year=2024)
rules, updates = parse(data)

ONE, TWO = 0, 0
for update in updates:
    # If valid, add middle (Part 1)
    if validate(update, rules):
        ONE += update[len(update) // 2]
    # Otherwise, topsort and add middle (Part 2)
    else:
        updatesort = topsort(update, rules)
        TWO += updatesort[len(updatesort) // 2]
print("ONE:", ONE)
print("TWO:", TWO)
