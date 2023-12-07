from functools import reduce

data = [x.strip() for x in open("../_input/2023/day04.txt")]

one = 0
for x in data:
    l = x.split("|")
    w = list(map(int, l[0].split(":")[1].split()))
    g = list(map(int, l[1].split()))
    ins = [x in w for x in g]
    score = reduce(lambda a, c: a * 2 if c and a != 0 else 1 if c else a, ins)
    one += score if score else 0
print("ONE:", one)

n = [1 for _ in data]
for k, x in enumerate(data):
    l = x.split("|")
    w = list(map(int, l[0].split(":")[1].split()))
    g = list(map(int, l[1].split()))
    c = sum(1 for x in w if x in g)
    for i in range(c):
        n[k + i + 1] += n[k]

print("TWO:", sum(n))
