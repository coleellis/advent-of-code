"""
--- Day 22: Monkey Market ---
"""

from aocd import get_data


def get_random(s):
    """Get random number from seed"""
    s = ((s << 6) ^ s) % 16777216
    s = ((s >> 5) ^ s) % 16777216
    s = ((s << 11) ^ s) % 16777216
    return s


data = get_data(day=22, year=2024)
nums = map(int, data.splitlines())

ONE = 0
for n in nums:
    seed = n
    for _ in range(2000):
        seed = get_random(seed)
    ONE += seed
print("ONE:", ONE)

lst = {}
nums = map(int, data.splitlines())
for n in nums:
    seed = n
    vis = set()
    chg = []

    for _ in range(2000):
        ns = get_random(seed)
        chg.append((ns % 10) - (seed % 10))
        seed = ns

        if len(chg) == 4:
            key = ",".join(map(str, chg))
            if key not in vis:
                if key not in lst:
                    lst[key] = []
                lst[key].append(ns % 10)
                vis.add(key)
            chg.pop(0)

print("TWO:", max(sum(v) for v in lst.values()))
