"""
--- Day 5: How About a Nice Game of Chess? ---
"""
from hashlib import md5
from aocd import get_data

stream = get_data(year=2016, day=5).strip()

ONE = ""
TWO = [""] * 8
i = 0
while len(ONE) < 8 or "" in TWO:
    H = md5((stream + str(i)).encode()).hexdigest()
    if H.startswith("00000"):
        if len(ONE) < 8:
            ONE += H[5]
        if H[5].isdigit() and int(H[5]) < 8 and TWO[int(H[5])] == "":
            TWO[int(H[5])] = H[6]
    i += 1
print("Part 1:", ONE)
print("Part 2:", "".join(TWO))
