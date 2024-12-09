"""
--- Day 8: Resonant Collinearity ---
"""

from aocd import get_data

# Get data
data = get_data(day=9, year=2024)
num = data.strip()

# Get expanded list
exp = []
for i, r in enumerate(num):
    if i % 2 == 0:
        for k in range(int(r)):
            exp.append(f"{i // 2}")
    else:
        for k in range(int(r)):
            exp.append(".")

L, R = 0, len(exp) - 1

# Swappages
while L < R:
    while exp[L] != ".":
        L += 1
    while exp[R] == ".":
        R -= 1

    # Swap
    exp[L] = exp[R]
    exp[R] = "."

    L += 1
    R -= 1

ONE = sum(k * int(v) for k, v in enumerate(exp) if v != ".")
print("ONE:", ONE)

used, free = {}, []

# Used and free
cnt = 0
for i, r in enumerate([int(i) for i in num]):
    start, end = cnt, cnt + r
    if i % 2 == 0:
        used[i // 2] = (start, end)
    elif r > 0:
        free.append((start, end))
    cnt += r

idx = max(used.keys())
while idx >= 0:
    # Enumerate start and end
    fs, fe = used[idx]
    fl = fe - fs

    fp = 0
    while fp < len(free):
        # Get gap
        gs, ge = free[fp]
        if gs >= fs:
            break

        gl = ge - gs
        if fl <= gl:
            free.pop(fp)

            # New file
            nfs, nfe = gs, gs + fl
            ngs, nge = nfe, ge

            # Insert file if it fits
            used[idx] = (nfs, nfe)
            if ngs != nge:
                free.insert(fp, (ngs, nge))
            break
        else:
            fp += 1

    idx -= 1

TWO = 0
for k, (start, end) in used.items():
    TWO += sum(k * i for i in range(start, end))
print("TWO:", TWO)
