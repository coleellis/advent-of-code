"""
--- Day 7: Some Assembly Required ---
"""

from aocd import get_data

stream = get_data(day=7, year=2015).splitlines()

vv, cc = {}, {}
for line in stream:
    ops, res = line.split(" -> ")
    cc[res] = ops.split(" ")


def solve(v):
    """Backtrack to find a value in the circuit"""
    try:
        return int(v)
    except ValueError:
        pass

    if v not in vv:
        op = cc[v]
        if len(op) == 1:
            vv[v] = solve(op[0])
        elif op[0] == "NOT":
            vv[v] = ~solve(op[1])
        elif op[1] == "AND":
            vv[v] = solve(op[0]) & solve(op[2])
        elif op[1] == "OR":
            vv[v] = solve(op[0]) | solve(op[2])
        elif op[1] == "LSHIFT":
            vv[v] = solve(op[0]) << solve(op[2])
        elif op[1] == "RSHIFT":
            vv[v] = solve(op[0]) >> solve(op[2])
        else:
            raise ValueError("Invalid input")
    return vv[v]


one = solve("a")
print("Part 1:", one)

vv = {}
vv["b"] = one
print("Part 2:", solve("a"))
