"""
--- Day 19: Medicine for Rudolph ---
"""

import re
from aocd import get_data

stream = get_data(year=2015, day=19).split("\n\n")

rr = re.findall(r"(\w+) => (\w+)", stream[0])
ss = stream[1]
dd = set()
for r in rr:
    for m in re.finditer(r[0], ss):
        dd.add(ss[: m.start()] + r[1] + ss[m.end() :])
print("Part 1:", len(dd))

ss = ss[::-1]
rr = {m[1][::-1]: m[0][::-1] for m in re.findall(r"(\w+) => (\w+)", stream[0])}
TWO = 0
while ss:
    ss = re.sub("|".join(rr.keys()), lambda z: rr[z.group()], ss, 1)
    ss = ss.replace("e", "")
    TWO += 1
print("Part 2:", TWO)
