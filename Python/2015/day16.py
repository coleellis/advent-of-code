"""
--- Day 16: Aunt Sue ---
"""

from aocd import get_data

stream = get_data(year=2015, day=16).splitlines()

goal = {
    "children": 3,
    "cats": 7,
    "samoyeds": 2,
    "pomeranians": 3,
    "akitas": 0,
    "vizslas": 0,
    "goldfish": 5,
    "trees": 3,
    "cars": 2,
    "perfumes": 1,
}

for line in stream:
    nn = int(line.split()[1].strip(":"))
    ll = [x.strip(":").strip(",") for x in line.split()]
    d = {ll[i]: int(ll[i + 1]) for i in range(2, len(ll), 2)}
    if all(goal[k] == d[k] for k in d):
        print("Part 1:", nn)
        break

for line in stream:
    nn = int(line.split()[1].strip(":"))
    ll = [x.strip(":").strip(",") for x in line.split()]
    d = {ll[i]: int(ll[i + 1]) for i in range(2, len(ll), 2)}
    if (
        all(goal[k] < d[k] for k in d if k in ["cats", "trees"])
        and all(goal[k] > d[k] for k in d if k in ["pomeranians", "goldfish"])
        and all(
            goal[k] == d[k]
            for k in d
            if k not in ["cats", "trees", "pomeranians", "goldfish"]
        )
    ):
        print("Part 2:", nn)
