"""
--- Day 22: Wizard Simulator 20XX ---
"""

from aocd import get_data

stream = get_data(year=2015, day=22).splitlines()


def sim(aa, n):
    """Simulate the battle"""
    bb = {"hp": int(stream[0].split()[-1]), "dmg": int(stream[1].split()[-1])}
    pp = {"hp": 50, "mana": 500, "armor": 0}
    tc = 0
    m = 0
    ee = {"S": 0, "P": 0, "R": 0}
    my = 1
    ss = {"M": 53, "D": 73, "S": 113, "P": 173, "R": 229}

    while True:
        if len(aa) - 1 < tc:
            print("out of moves")
            return 0
        if ee["P"]:
            ee["P"] = max(ee["P"] - 1, 0)
            bb["hp"] -= 3
        if ee["S"]:
            ee["S"] = max(ee["S"] - 1, 0)
            pp["armor"] = 7
        else:
            pp["armor"] = 0
        if ee["R"]:
            ee["R"] = max(ee["R"] - 1, 0)
            pp["mana"] += 101
        if my == 1:
            if n == 2:
                pp["hp"] -= 1
                if pp["hp"] <= 0:
                    return 0

            a = aa[tc]
            pp["mana"] -= ss[a]
            m += ss[a]

            if a == "M":
                bb["hp"] -= 4
            elif a == "D":
                bb["hp"] -= 2
                pp["hp"] += 2
            elif a == "S":
                if ee["S"]:
                    return 0
                ee["S"] = 6
            elif a == "P":
                if ee["P"]:
                    return 0
                ee["P"] = 6
            elif a == "R":
                if ee["R"]:
                    return 0
                ee["R"] = 5
            if pp["mana"] < 0:
                return 0

        if bb["hp"] <= 0:
            return m
        if my == -1:
            pp["hp"] -= max(bb["dmg"] - pp["armor"], 1)
            if pp["hp"] <= 0:
                return 0
        if my == 1:
            tc += 1
        my = -my


def iterate(pos):
    """Iterate through all possible actions"""
    a[pos] = "DSPRM"["MDSPR".index(a[pos])]
    if a[pos] == "M" and pos + 1 <= len(a):
        iterate(pos + 1)


for part in (1, 2):
    a = ["M"] * 20
    MM = 1e6
    for i in range(int(1e6)):
        RR = sim(a, part)
        if RR:
            MM = min(RR, MM)
        iterate(0)
    print(f"Part {part}: {MM}")
