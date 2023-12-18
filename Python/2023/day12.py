"""
--- Day 12: Hot Springs ---
"""
from aocd import get_data

stream = get_data(day=12, year=2023).splitlines()
data = [x.strip() for x in stream]
grid = {}


def score(line, goal, li, gi, bl):
    """Builds DP table to find number of permutations of line that match goal"""
    key = (li, gi, bl)
    if key in grid:
        return grid[key]
    if li == len(line):
        if gi == len(goal) and bl == 0:
            return 1
        if gi == len(goal) - 1 and goal[gi] == bl:
            return 1
        return 0

    ret = 0
    for c in [".", "#"]:
        if c == line[li] or line[li] == "?":
            if c == "." and bl == 0:
                ret += score(line, goal, li + 1, gi, 0)
            elif c == "." and bl > 0 and gi < len(goal) and goal[gi] == bl:
                ret += score(line, goal, li + 1, gi + 1, 0)
            elif c == "#":
                ret += score(line, goal, li + 1, gi, bl + 1)
    grid[key] = ret
    return ret


for second in [False, True]:
    PART = 0
    for line in data:
        line, goal = line.split(" ")
        if second:
            line = "?".join([line for _ in range(5)])
            goal = ",".join([goal for _ in range(5)])
        goal = [int(x) for x in goal.split(",")]
        grid.clear()
        zz = score(line, goal, 0, 0, 0)
        PART += zz
    print("Part {}:".format(2 if second else 1), PART)
