"""
--- Day 20: Infinite Elves and Infinite Houses ---
"""

from aocd import get_data

stream = get_data(year=2015, day=20).strip()


def sum_factors(n):
    """Sums the factors of n""" ""
    return sum(set(sum((i, n // i)) for i in range(1, int(n**0.5) + 1) if n % i == 0))


ONE = 0
while sum_factors(ONE) * 10 < int(stream):
    ONE += 1
print("Part 1:", ONE)

hh = [0] * (int(stream) // 10)
for i in range(1, len(hh)):
    print(i)
    D = 0
    for h in range(i, len(hh), i):
        print("  ", h)
        hh[h] += i * 10
        D += 1
        if D >= 50:
            break
    for k, p in enumerate(hh):
        if p >= int(stream):
            print("Part 2:", k)
            break
