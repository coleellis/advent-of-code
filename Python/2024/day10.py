"""
--- Day 10: Hoof It ---
"""

import networkx as nx
from aocd import get_data

data = get_data(day=10, year=2024)


grid = {
    i + 1j * j: int(x) for i, r in enumerate(data.splitlines()) for j, x in enumerate(r)
}

G = nx.DiGraph(
    (x, x + dx)
    for x, y in grid.items()
    for dx in (-1, 1, -1j, 1j)
    if grid.get(x + dx) == y + 1
)

ss, ee = [[x for x, y in grid.items() if y == v] for v in (0, 9)]
P = [list(nx.all_simple_paths(G, s, e)) for s in ss for e in ee]
print("ONE:", sum(map(any, P)))
print("TWO:", sum(map(len, P)))
