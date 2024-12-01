"""
--- Day 18: Like a GIF For Your Yard ---
"""

from aocd import get_data

stream = get_data(day=18, year=2015).splitlines()
og = [[c == "#" for c in line] for line in stream]


def neighbors(gg, x, y):
    """Gets number of turned on neighbors"""
    return sum(
        gg[i][j]
        for i in range(x - 1, x + 2)
        for j in range(y - 1, y + 2)
        if (i, j) != (x, y) and 0 <= i < len(gg) and 0 <= j < len(gg[0])
    )


def step(gg):
    """Gets next step of grid"""
    return [
        [
            (neighbors(gg, i, j) == 3 or (gg[i][j] and neighbors(gg, i, j) == 2))
            for j in range(len(gg[0]))
        ]
        for i in range(len(gg))
    ]


g = og
for _ in range(100):
    g = step(g)
print("Part 1:", sum(sum(row) for row in g))

g = og
g[0][0] = g[0][-1] = g[-1][0] = g[-1][-1] = True
for _ in range(100):
    g = step(g)
    g[0][0] = g[0][-1] = g[-1][0] = g[-1][-1] = True
print("Part 2:", sum(sum(row) for row in g))
