"""
--- Day 25: Let It Snow ---
"""
from aocd import get_data

stream = get_data(year=2015, day=25).split()
r, c = int(stream[-3][:-1]), int(stream[-1][:-1])


def t(n):
    """Return the nth triangular number"""
    return n * (n + 1) // 2


def gen(n):
    """Generate the nth code"""
    return (20151125 * pow(252533, n - 1, 33554393)) % 33554393


cc = t(r + c - 1) - r + 1
print(gen(cc))
