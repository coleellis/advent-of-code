import re
from aocd import get_data

data = get_data(day=13, year=2024).split("\n\n")

# Regex to get the numbers
lst = []
for g in data:
    lst.append(list(map(int, re.findall(r"(\d+)", g))))


def run(games, flag=False):
    """Get number of tokens"""
    tokens = 0
    for ax, ay, bx, by, x, y in games:
        if flag:
            x += 10000000000000
            y += 10000000000000
        a = round((y - ((by * x) / bx)) / (ay - ((by * ax) / bx)))
        b = round((x - ax * a) / bx)
        if ax * a + bx * b == x and ay * a + by * b == y:
            tokens += a * 3 + b

    return tokens


print("ONE:", run(lst, False))
print("TWO:", run(lst, True))
