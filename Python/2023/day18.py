"""
--- Day 18: Lavaduct Lagoon ---
"""

from skspatial.measurement import area_signed
from aocd import get_data

stream = get_data(day=18, year=2023).splitlines()
data = [line.split() for line in stream]

code = {"0": "R", "1": "D", "2": "L", "3": "U"}
dirs = {"R": (0, 1), "L": (0, -1), "U": (-1, 0), "D": (1, 0)}


ss = []
x, y, p = 0, 0, 0
for line in data:
    d, l, _ = line
    l = int(l)
    dx, dy = dirs[d]
    x, y, p = x + dx * l, y + dy * l, p + l
    ss.append((x, y))
print("Part 1:", abs(area_signed(ss)) + p // 2 + 1)

ss = []
x, y, p = 0, 0, 0
for line in data:
    _, _, h = line
    h = h[2:8]
    d, l = code[h[-1]], int(h[:-1], 16)
    dx, dy = dirs[d]
    x, y, p = x + dx * l, y + dy * l, p + l
    ss.append((x, y))
print("Part 2:", abs(area_signed(ss)) + p // 2 + 1)
