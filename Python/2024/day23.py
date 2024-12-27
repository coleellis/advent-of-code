"""
--- Day 23: LAN Party ---
"""

import networkx as nx
from aocd import get_data

data = get_data(day=23, year=2024)

# Build Graph
G = nx.Graph()
for ln in data.splitlines():
    l, r = ln.split("-")
    G.add_edge(l, r)

# Run the cliques
tt = [list(t) for t in nx.enumerate_all_cliques(G) if len(t) == 3]
ft = [t for t in tt if any(n.startswith("t") for n in t)]
print("ONE:", len(ft))

# Get the largest clique
cc = list(nx.find_cliques(G))
lc = max(cc, key=len)
print("TWO:", ",".join(sorted(lc)))
