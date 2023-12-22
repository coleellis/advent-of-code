"""
--- Day 22: Sand Slabs ---
"""
from aocd import get_data

stream = get_data(day=22, year=2023).splitlines()
data = [[list(map(int, y.split(","))) for y in l.split("~")] for l in stream]

gg, bd, bu, br = {}, {}, {}, []
ONE = TWO = 0

for bb in sorted(data, key=lambda x: min([x[0][2], x[1][2]])):
    # get all possible coordinates for this bridge
    x, y, z = [
        list(range(*((b := sorted([bb[0][a], bb[1][a]]))[0], b[1] + 1)))
        for a in range(3)
    ]
    bb = set()
    while z[0] > 1 and not any((a, b, c - 1) in gg for a in x for b in y for c in z):
        z = [z[0] - 1] + z[:-1]
    # if this bridge is not connected to any other bridges
    br.append(bb := tuple(sorted({(a, b, c) for a in x for b in y for c in z})))
    bd[bb] = set()
    z_min = min(z[2] for z in bb)
    for x, y, z in bb:
        gg[x, y, z] = bb
        if z == z_min and (x, y, z - 1) in gg:
            db = gg[x, y, z - 1]
            bd[bb].add(db)
            bu[db] = bu.get(db, set()) | {bb}

for bb in br:
    # if bb has no up connections or all up connections have more than ONE down connection
    if not (up := bu.get(bb, [])) or all([len(bd.get(x, [])) > 1 for x in up]):
        ONE += 1
    # BFS from bb to find all connected bridges
    q = [bb]
    fb = {bb}
    while q:
        c = q.pop()
        for n in bu.get(c, set()):
            if not bd[n] - fb:
                fb.add(n)
                q.append(n)
    TWO += len(fb - {bb})

print("Part 1:", ONE)
print("Part 2:", TWO)
