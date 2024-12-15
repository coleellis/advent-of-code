import re
from aocd import get_data

data = get_data(day=14, year=2024)

g = [0 for _ in range(4)]
for l in data.splitlines():
    r = [int(n) for n in re.findall(r"[-\d]+", l)]
    x, y = (r[0] + (100 * r[2])) % 101, (r[1] + (100 * r[3])) % 103
    if x < 50 and y < 51:
        g[0] += 1
    elif x > 50 and y < 51:
        g[1] += 1
    elif x < 50 and y > 51:
        g[2] += 1
    elif x > 50 and y > 51:
        g[3] += 1
print("ONE:", g[0] * g[1] * g[2] * g[3])

rr = [[int(n) for n in re.findall(r"[-\d]+", line)] for line in data.splitlines()]
for i in range(1000000):
    for j in range(103):
        r, n = sorted({rb[0] for rb in rr if rb[1] == j}), 0
        for k in range(len(r) - 1):
            n = n + 1 if r[k + 1] == r[k] + 1 else 0
            if n > 10:
                print("TWO", i)
                quit()
    for r in rr:
        r[0], r[1] = (r[0] + r[2]) % 101, (r[1] + r[3]) % 103
