data = [x.strip() for x in open("input.txt").readlines()]

total = 0
for line in data:
    score = 0
    line = line.split("|")
    winning = line[0].split(":")[1].strip().split(" ")
    given = [x for x in line[1].strip().split(" ") if x != ""]
    for x in given:
        if x in winning:
            score = 1 if score == 0 else score * 2
    total += score

print(total)

num = [1 for x in data]
count_next = 0
for l, line in enumerate(data):
    line = line.split("|")
    winning = line[0].split(":")[1].strip().split(" ")
    given = [x for x in line[1].strip().split(" ") if x != ""]
    for x in given:
        if x in winning:
            count_next += 1
    for idx in range(count_next):
        num[l + idx + 1] += num[l]
    count_next = 0


print(sum(num))
