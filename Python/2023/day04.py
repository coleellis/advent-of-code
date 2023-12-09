"""
--- Day 4: Scratchcards ---
"""
from functools import reduce
from aocd import get_data

stream = get_data(day=4, year=2023)

data = [x.strip() for x in stream.split("\n")]

ONE = 0
for x in data:
    l = x.split("|")
    w = list(map(int, l[0].split(":")[1].split()))
    g = list(map(int, l[1].split()))
    ins = [x in w for x in g]
    score = reduce(lambda a, c: a * 2 if c and a != 0 else 1 if c else a, ins)
    ONE += score if score else 0
print("ONE:", ONE)

n = [1 for _ in data]
for k, x in enumerate(data):
    l = x.split("|")
    w = list(map(int, l[0].split(":")[1].split()))
    g = list(map(int, l[1].split()))
    c = sum(1 for x in w if x in g)
    for i in range(c):
        n[k + i + 1] += n[k]

print("TWO:", sum(n))
