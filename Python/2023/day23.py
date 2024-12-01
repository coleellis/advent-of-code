"""
--- Day 23: A Long Walk ---
"""

import networkx as nx
from networkx.classes.function import path_weight
from aocd import get_data

stream = get_data(day=23, year=2023).split()
SPEC = {">": (0, -1), "<": (0, 1), "^": (1, 0), "v": (-1, 0)}

N, M = len(stream), len(stream[0])
s, t = (0, 1), (N - 1, M - 2)

G = nx.grid_2d_graph(N, M, create_using=nx.DiGraph)
G2 = nx.grid_2d_graph(N, M)
for i, l in enumerate(stream):
    for j, c in enumerate(l):
        if c == "#":
            G.remove_node((i, j))
        elif c in SPEC:
            di, dj = SPEC[c]
            G.remove_edge((i, j), (i + di, j + dj))

print("Part 1:", max(map(len, nx.all_simple_edge_paths(G, s, t))))

tn = [n for n in G2.nodes if len(G2.edges(n)) == 2]
for n in tn:
    v1, v2 = list(G2.neighbors(n))
    new_weight = sum(G2.edges[n, v].get("d", 1) for v in (v1, v2))
    G2.add_edge(v1, v2, d=new_weight)
    G2.remove_node(n)

print(
    "Part 2:", max(path_weight(G2, path, "d") for path in nx.all_simple_paths(G2, s, t))
)
