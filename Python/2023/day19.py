"""
--- Day 19: Aplenty ---
"""
import re
from functools import reduce
from math import prod
import portion as P
from aocd import get_data

stream = get_data(day=19, year=2023).split("\n\n")


def parse(line):
    """Convert the rule into a list of COND, T, F lists"""
    l = line
    n = None
    if "{" in line:
        l = line[:-1].split("{")[1]
        n = line[:-1].split("{")[0]
    f = ",".join(l.split(",")[1:])
    if "," in f:
        f = parse(f)
    if n:
        return n, [l.split(":")[0], l.split(":")[1].split(",")[0], f]
    return [l.split(":")[0], l.split(":")[1].split(",")[0], f]


rules = {}
for r in stream[0].splitlines():
    z = parse(r)
    rules[z[0]] = z[1]

ss = []
for s in stream[1].splitlines():
    s = eval(
        re.sub(r"(\w+)=(-?\d+)", r'"\1": \2', s)
        .replace("=", ": ")
        .replace("{", "{ ")
        .replace("}", " }")
    )
    ss.append(s)


def check(json, rule):
    """parse the rule"""
    if "<" in rule[0]:
        r = rule[0].split("<")
        if json[r[0]] < int(r[1]):
            return rule[1]
    else:
        r = rule[0].split(">")
        if json[r[0]] > int(r[1]):
            return rule[1]
    return rule[2]


def recurse(xmas, rule):
    """Recursively find the number of valid combinations"""
    nx1, nx2, cc = xmas.copy(), xmas.copy(), 0
    # base case: at accept/reject
    if rule in ["A", "R"]:
        return (
            0
            if rule == "R"
            else prod(len(list(P.iterate(b, step=1))) for b in xmas.values())
        )
    if isinstance(rule, str):
        rule = rules[rule]

    # parse the rule
    if "<" in rule[0]:
        o, v = rule[0].split("<")
        if int(v) < xmas[o].lower:
            cc += recurse(xmas, rule[2])
        elif int(v) > xmas[o].upper:
            cc += recurse(xmas, rule[1])
        else:
            nx1[o] &= P.closed(xmas[o].lower, int(v) - 1)
            cc += recurse(nx1, rule[1])
            nx2[o] &= P.closed(int(v), xmas[o].upper)
            cc += recurse(nx2, rule[2])
    else:
        o, v = rule[0].split(">")
        if int(v) > xmas[o].upper:
            cc += recurse(xmas, rule[2])
        elif int(v) < xmas[o].lower:
            cc += recurse(xmas, rule[1])
        else:
            nx1[o] &= P.closed(int(v) + 1, xmas[o].upper)
            cc += recurse(nx1, rule[1])
            nx2[o] &= P.closed(xmas[o].lower, int(v))
            cc += recurse(nx2, rule[2])
    return cc


ONE = 0
for s in ss:
    q = check(s, rules["in"])
    while q not in ["A", "R"]:
        q = check(s, q) if isinstance(q, list) else check(s, rules[q])
    if q == "A":
        ONE += reduce(lambda x, y: x + y, [s[k] for k in s.keys()])
print("Part 1:", ONE)

xmas = {k: P.closed(1, 4000) for k in "xmas"}
print("Part 2:", recurse(xmas, rules["in"]))
