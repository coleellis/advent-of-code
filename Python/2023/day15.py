"""
--- Day 15: Lens Library ---
"""
from aocd import get_data

stream = get_data(day=15, year=2023).strip().split(',')

def hasher(s):
    """hasher function for a line"""
    t = 0
    for c in s:
        t += ord(c)
        t *= 17
        t %= 256
    return t

ONE = 0
for l in stream:
    ONE += hasher(l)
print("Part 1:", ONE)

m = [{} for _ in range(256)]
for l in stream:
    if l.find('-') != -1:
        l = l.split('-')[0]
        hh = hasher(l)
        m[hh].pop(l, None)
    else:
        l = l.split('=')
        hh = hasher(l[0])
        m[hh][l[0]] = int(l[1])

TWO = 0
for i, box in enumerate(m):
    for j, k in enumerate(box):
        TWO += (i+1) * (j+1) * box[k]
print("Part 2:", TWO)
