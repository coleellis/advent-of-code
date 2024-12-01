"""
--- Day 20: Pulse Propagation ---
"""

from math import prod
from aocd import get_data

stream = get_data(day=20, year=2023).splitlines()


class Module:
    """Module with input, output, type, next, and state"""

    def __init__(self, l) -> None:
        p = l.split(" -> ")
        self.n = p[0]
        if p[0][0] in "%&":
            self.t = p[0][0]
            self.n = "".join(p[0][1:])
        else:
            self.t = ""
            self.n = p[0]
        self.nx = p[1].split(", ")
        self.st = False
        self.i = {}


mm = {}
for l in stream:
    m = Module(l)
    mm[m.n] = m

for m in mm:
    if mm[m].t == "&":
        mm[m].i = {}
        for d in mm:
            if m in mm[d].nx:
                mm[m].i[d] = False

hh, ll = 0, 0
for _ in range(1000):
    ss = [("broadcaster", False)]

    while ss:
        src, sig = ss.pop(0)

        dst = []
        out = sig

        if sig:
            hh += 1
        else:
            ll += 1

        if src in mm and mm[src].t == "":
            dst = mm[src].nx
        elif src in mm and mm[src].t == "%" and not sig:
            out = mm[src].st = not mm[src].st
            dst = mm[src].nx
        elif src in mm and mm[src].t == "&":
            out = not all(mm[src].i.values())
            dst = mm[src].nx

        for m in dst:
            ss.append((m, out))
            if m in mm and mm[m].t == "&":
                mm[m].i[src] = out
print("Part 1:", hh * ll)


mm = {}
for l in stream:
    m = Module(l)
    mm[m.n] = m
    if "rx" in m.nx:
        p = m.n

for m in mm:
    if mm[m].t == "&":
        mm[m].i = {}
        for d in mm:
            if m in mm[d].nx:
                mm[m].i[d] = False

cycles = {m: 0 for m in mm[p].i}

CC = 0
while not all(cycles.values()):
    CC += 1
    ss = [("broadcaster", False)]

    while ss:
        src, sig = ss.pop(0)
        dst = []
        out = sig

        if src in mm and mm[src].t == "":
            dst = mm[src].nx
        elif src in mm and mm[src].t == "%" and not sig:
            out = mm[src].st = not mm[src].st
            dst = mm[src].nx
        elif src in mm and mm[src].t == "&":
            out = not all(mm[src].i.values())
            dst = mm[src].nx

            if src == p and any(mm[src].i.values()):
                for m in mm[src].i:
                    if mm[src].i[m]:
                        cycles[m] = CC

        for m in dst:
            ss.append((m, out))
            if m in mm and mm[m].t == "&":
                mm[m].i[src] = out
print("Part 2:", prod(cycles.values()))
