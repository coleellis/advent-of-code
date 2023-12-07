data = open("../_input/2023/day02.txt").read().splitlines()

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
        passing = True
        for a in c:
            x, y = a.split(" ")
            if y == "red" and int(x) > red:
                passing = False
            elif y == "green" and int(x) > green:
                passing = False
            elif y == "blue" and int(x) > blue:
                passing = False
        if passing:
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
