"""
--- Day 21: RPG Simulator 20XX ---
"""
from itertools import combinations
from aocd import get_data

stream = get_data(year=2015, day=21).splitlines()

boss = {
    "hp": int(stream[0].split()[-1]),
    "damage": int(stream[1].split()[-1]),
    "armor": int(stream[2].split()[-1]),
}
p = {"hp": 100, "damage": 0, "armor": 0}

ww = {
    "Dagger": {"cost": 8, "damage": 4, "armor": 0},
    "Shortsword": {"cost": 10, "damage": 5, "armor": 0},
    "Warhammer": {"cost": 25, "damage": 6, "armor": 0},
    "Longsword": {"cost": 40, "damage": 7, "armor": 0},
    "Greataxe": {"cost": 74, "damage": 8, "armor": 0},
}

aa = {
    "Leather": {"cost": 13, "damage": 0, "armor": 1},
    "Chainmail": {"cost": 31, "damage": 0, "armor": 2},
    "Splintmail": {"cost": 53, "damage": 0, "armor": 3},
    "Bandedmail": {"cost": 75, "damage": 0, "armor": 4},
    "Platemail": {"cost": 102, "damage": 0, "armor": 5},
    "None": {"cost": 0, "damage": 0, "armor": 0},
}

rr = {
    "Damage +1": {"cost": 25, "damage": 1, "armor": 0},
    "Damage +2": {"cost": 50, "damage": 2, "armor": 0},
    "Damage +3": {"cost": 100, "damage": 3, "armor": 0},
    "Defense +1": {"cost": 20, "damage": 0, "armor": 1},
    "Defense +2": {"cost": 40, "damage": 0, "armor": 2},
    "Defense +3": {"cost": 80, "damage": 0, "armor": 3},
    "None": {"cost": 0, "damage": 0, "armor": 0},
}


def fight(pp, bb):
    """Simulate a fight"""
    while True:
        bb["hp"] -= max(1, pp["damage"] - bb["armor"])
        if bb["hp"] <= 0:
            return True
        pp["hp"] -= max(1, bb["damage"] - pp["armor"])
        if pp["hp"] <= 0:
            return False


C = 1e3
for w in ww.items():
    for a in aa.items():
        for r1, r2 in combinations(rr, 2):
            p["damage"] = (
                ww[w]["damage"] + aa[a]["damage"] + rr[r1]["damage"] + rr[r2]["damage"]
            )
            p["armor"] = (
                ww[w]["armor"] + aa[a]["armor"] + rr[r1]["armor"] + rr[r2]["armor"]
            )
            p["cost"] = ww[w]["cost"] + aa[a]["cost"] + rr[r1]["cost"] + rr[r2]["cost"]
            if fight(p.copy(), boss.copy()):
                C = min(C, p["cost"])
print("Part 1:", int(C))

C = 0
for w in ww:
    for a in aa:
        for r1, r2 in combinations(rr, 2):
            p["damage"] = (
                ww[w]["damage"] + aa[a]["damage"] + rr[r1]["damage"] + rr[r2]["damage"]
            )
            p["armor"] = (
                ww[w]["armor"] + aa[a]["armor"] + rr[r1]["armor"] + rr[r2]["armor"]
            )
            p["cost"] = ww[w]["cost"] + aa[a]["cost"] + rr[r1]["cost"] + rr[r2]["cost"]
            if not fight(p.copy(), boss.copy()):
                C = max(C, p["cost"])
print("Part 2:", int(C))
