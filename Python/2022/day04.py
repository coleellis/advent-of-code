"""
--- Day 4: Camp Cleanup ---
"""

from aocd import get_data

stream = get_data(day=3, year=2022)


def contains(x, y):
    """Returns whether all of x is in y, or all of y is in x"""
    xx = [int(a) for a in x.split("-")]
    yy = [int(a) for a in y.split("-")]
    return all(z in range(xx[0], xx[1] + 1) for z in range(yy[0], yy[1] + 1)) or all(
        z in range(yy[0], yy[1] + 1) for z in range(xx[0], xx[1] + 1)
    )


def overlap(x, y):
    """Returns whether any of x is in y, or any of y is in x"""
    xx = [int(a) for a in x.split("-")]
    yy = [int(a) for a in y.split("-")]
    return any(z in range(xx[0], xx[1] + 1) for z in range(yy[0], yy[1] + 1)) or any(
        z in range(yy[0], yy[1] + 1) for z in range(xx[0], xx[1] + 1)
    )


lines = [x.split(",") for x in stream.split("\n")]

one = sum([1 for x in lines if contains(x[0], x[1])])
print("Part 1:", one)

two = sum([1 for x in lines if overlap(x[0], x[1])])
print("Part 2:", two)
