"""
--- Day 16: Reindeer Maze ---
"""

from collections import namedtuple
from math import sqrt
from aocd import get_data


Point = namedtuple("Point", ["y", "x"])
Node = namedtuple("Node", ["p", "d"])

data = get_data(day=16, year=2024)
rows = data.splitlines()
width = len(rows[0])
grid = list(map(list, rows))
start, end = Point(*divmod(data.find("S"), width + 1)), Point(
    *divmod(data.find("E"), width + 1)
)


def heuristic(p):
    """Cost Heuristic"""
    return sqrt((p.x - end.x) ** 2 + (p.y - end.y) ** 2)


def backtrace(parent, cost, cur):
    """Equal Cost Backtracing"""
    last = cur.d

    trace = {cur.p}
    while cur := parent.get(cur):
        trace.add(cur.p)
        for d in map(lambda o: (cur.d + o) & 3, [1, -1]):
            test = Node(cur.p, d)
            if last != cur.d and (cost.get(test, 0) - cost[cur]) == 1000:
                trace.update(backtrace(parent, cost, parent.get(test)))

        last = cur.d

    return trace


def run():
    """Run A* search"""
    t_start = Node(start, 0)

    pending = {t_start}
    parent = {}
    node_cost = {t_start: 0.0}
    tc = {t_start: heuristic(t_start.p)}

    while len(pending) > 0:
        cur = min(pending, key=lambda t: tc[t])

        # Check for end node
        if cur.p == end:
            return int(node_cost[cur]), len(backtrace(parent, node_cost, cur))

        pending.remove(cur)

        # Scan all directions
        for i, v in enumerate([(0, 1), (1, 0), (0, -1), (-1, 0)]):
            n = Node(Point(cur.p.y + v[0], cur.p.x + v[1]), i)
            if grid[n.p.y][n.p.x] == "#":
                continue

            nc = node_cost[cur] + [0, 1000, 2000, 1000][(i - cur.d) & 3] + 1
            if nc >= node_cost.get(n, 1e13):
                continue

            parent[n] = cur
            node_cost[n] = nc
            tc[n] = nc + heuristic(n.p)

            if n in pending:
                continue

            pending.add(n)

    return 0, 0


ONE, TWO = run()
print("ONE:", ONE)
print("TWO:", TWO)
