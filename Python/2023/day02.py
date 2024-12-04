"""
--- Day 2: Cube Conundrum ---
"""

from aocd import get_data

data = get_data(day=2, year=2023).split("\n")
# Data = open("test.txt").read().split("\n")

red = 12
green = 13
blue = 14

total = 0
for line in data:
    id = line.split(":")[0].split(" ")[1]
    turns = line.split(":")[1].strip().split("; ")
    n = 0
    for t in turns:
        c = t.split(", ")
        PASSING = True
        for a in c:
            x, y = a.split(" ")
            if y == "red" and int(x) > red:
                PASSING = False
            elif y == "green" and int(x) > green:
                PASSING = False
            elif y == "blue" and int(x) > blue:
                PASSING = False
        if PASSING:
            n += 1
    if n == len(turns):
        total += int(id)

print("ONE:", total)

total = 0
for line in data:
    power = 1
    maxes = {red: 0, green: 0, blue: 0}
    id = line.split(":")[0].split(" ")[1]
    turns = line.split(":")[1].strip().split("; ")
    n = 0
    for t in turns:
        c = t.split(", ")
        for a in c:
            x, y = a.split(" ")
            if y == "red":
                maxes[red] = max(maxes[red], int(x))
            elif y == "green":
                maxes[green] = max(maxes[green], int(x))
            elif y == "blue":
                maxes[blue] = max(maxes[blue], int(x))
    for m in maxes:
        power *= maxes[m]
    total += power

print("TWO:", total)
