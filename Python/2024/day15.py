"""
--- Day 15: Warehouse Woes ---
"""

from aocd import get_data


def canmove(pos, d, ignore=False):
    if f[pos] == ".":
        return True
    if f[pos] == "#":
        return False
    if d in ["^", "v"] and not ignore:
        if f[pos] == "[" and not canmove(pos + 1, d, True):
            return False
        if f[pos] == "]" and not canmove(pos - 1, d, True):
            return False
    if canmove(pos + dirs[d], d):
        return True
    return False


def move(pos, d, ignore=False):
    if not canmove(pos, d):
        return False
    if f[pos] == ".":
        return True
    if d in ["^", "v"] and not ignore:
        if f[pos] == "[":
            move(pos + 1, d, True)
        if f[pos] == "]":
            move(pos - 1, d, True)
    move(pos + dirs[d], d)
    f[pos + dirs[d]] = f[pos]
    f[pos] = "."
    return True


data = get_data(day=15, year=2024)

for x in ["ONE", "TWO"]:
    # Reset grid
    f, m = data.split("\n\n")
    m = m.replace("\n", "")

    # Part 2 expansion
    if x == "TWO":
        f = (
            f.replace(".", "..")
            .replace("#", "##")
            .replace("O", "[]")
            .replace("@", "@.")
        )

    # Build floor
    f = f.splitlines()
    C, R = len(f[0]), len(f)
    f = list("".join(f))

    # Start
    dirs = {"^": -C, "v": C, "<": -1, ">": 1}
    pos = f.index("@")

    # Moves
    for mm in m:
        if move(pos, mm):
            pos = pos + dirs[mm]

    # Score
    score = sum(100 * (i // C) + i % C for i in range(len(f)) if f[i] in ["O", "["])
    print(f"{x}: {score}")
