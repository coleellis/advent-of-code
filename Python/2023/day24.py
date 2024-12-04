"""
--- Day 24: Never Tell Me The Odds ---
"""

import re
from itertools import combinations
import z3
from aocd import get_data

stream = get_data(day=24, year=2023).splitlines()
data = []
for ll in stream:
    p, v = ll.split("@")
    x, y, z = map(int, re.findall(r"-?\d+", p))
    vx, vy, vz = map(int, re.findall(r"-?\d+", v))
    data.append({"p": (x, y, z), "v": (vx, vy, vz)})


def intersect(pair, a, b):
    """Check if two lines intersect in the given range"""
    l1, l2 = pair
    p1, v1 = l1["p"], l1["v"]
    p2, v2 = l2["p"], l2["v"]
    # Find coordinates of intersection (just basic algebra)
    lhs = p1[1] - p2[1] + (v1[1] / v1[0]) * (p2[0] - p1[0])
    rhs = v2[1] - (v2[0] / v1[0]) * v1[1]
    if rhs == 0:
        return False
    if (ss := lhs / rhs) < 0:
        return False
    if (p2[0] - p1[0] + ss * v2[0]) / v1[0] < 0:
        return False
    xx, yy = p2[0] + ss * v2[0], p2[1] + ss * v2[1]
    return a <= xx <= b and a <= yy <= b


ONE = 0
for pp in combinations(data, 2):
    if intersect(pp, 200000000000000, 400000000000000):
        ONE += 1
print("Part 1:", ONE)

I = lambda n: z3.BitVec(n, 64)
x, y, z = I("x"), I("y"), I("z")
vx, vy, vz = I("vx"), I("vy"), I("vz")
s = z3.Solver()

for i, l in enumerate(data):
    (px, py, pz), (pvx, pvy, pvz) = l["p"], l["v"]
    t = I(f"t_{i}")
    s.add(t >= 0)
    s.add(x + vx * t == px + pvx * t)
    s.add(y + vy * t == py + pvy * t)
    s.add(z + vz * t == pz + pvz * t)

assert s.check() == z3.sat
m = s.model()
x, y, z = m.eval(x).as_long(), m.eval(y).as_long(), m.eval(z).as_long()
print("Part 2:", x + y + z)
