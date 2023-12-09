"""
--- Day 11: Monkey in the Middle ---
"""
from aocd import get_data

stream = get_data(day=11, year=2022).split("\n\n")

data = [x.strip().split("\n") for x in stream]
print(data[0])

m = {}
for i, x in enumerate(data):
    m[i] = [int(b) for b in x[1].split(":")[1].strip().split(", ")]
n = [0 for _ in m]

for zz in range(10000):
    for a, l in enumerate(data):
        for i in range(len(m[a])):
            # inspection
            n[a] += 1
            w = m[a][0]
            m[a].pop(0)
            # operation
            op = l[2].strip().split()[-2]
            r = l[2].strip().split()[-1]
            r = w if r == "old" else int(r)
            if op == "+":
                w += r
            else:
                w *= r
            # boredom
            w //= 3
            # testing
            f = l[3].strip().split()[-1]
            if w % int(f) == 0:
                m[int(l[4].strip().split()[-1])].append(w)
            else:
                m[int(l[5].strip().split()[-1])].append(w)

n.sort(reverse=True)
ans = n[0] * n[1]

print(ans)
