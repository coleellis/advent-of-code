from aocd import get_data


def delta(a, b):
    return (ord(b) - ord(a) - 23) % 3


def react(a, b):
    return (ord(b) - 64 + ord(a) - 64 - 25) % 3


d = [x.split() for x in get_data(day=2, year=2022).split("\n")]
one = 0
for x, y in d:
    s = delta(x, y)
    one += ord(y) - ord("W")
    one += 3 * s + 3 if s in (0, 1) else 0
print("Part 1:", one)

two = 0
for x, y in d:
    s = 3 if react(x, y) == 0 else react(x, y)
    two += s
    two += (ord(y) - ord("X")) * 3
print("Part 2:", two)
