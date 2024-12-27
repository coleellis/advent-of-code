"""
--- Day 24: Crossed Wires ---
"""

import operator
import re
from aocd import get_data

data = get_data(day=24, year=2024)
W, G = data.split("\n\n")

# Get wires
W = re.findall(r"(\w\d\d): (0|1)", W)
W = {k: int(v) for k, v in W}

# Get getes
G = re.findall(r"([\w\d]{3}) (AND|OR|XOR) ([\w\d]{3}) -> ([\w\d]{3})", G)
G = {k: (a, b, c) for a, b, c, k in G}

# Operators
OPS = {"AND": operator.and_, "OR": operator.or_, "XOR": operator.xor}


def one():
    """Part 1"""

    def evaluate(gate):
        a, op, b = gate
        for wire in (a, b):
            if wire not in W:
                W[wire] = evaluate(G[wire])
        return OPS[op](W[a], W[b])

    return int(
        "".join(
            str(evaluate(G[z]))
            for z in sorted(G.keys(), reverse=True)
            if z.startswith("z")
        ),
        2,
    )


def two():
    """Part 2"""
    return ",".join(
        sorted(
            c
            for c, (a, op, b) in G.items()
            if (
                (c.startswith("z") and op != "XOR" and c != "z45")
                or (
                    op == "XOR"
                    and all(not x.startswith(("x", "y", "z")) for x in (a, b, c))
                )
                or (
                    op == "AND"
                    and "x00" not in (a, b)
                    and any(
                        c in (aa, bb) and op2 != "OR" for (aa, op2, bb) in G.values()
                    )
                )
                or (
                    op == "XOR"
                    and any(
                        c in (aa, bb) and op2 == "OR" for (aa, op2, bb) in G.values()
                    )
                )
            )
        )
    )


print("ONE:", one())
print("TWO:", two())
