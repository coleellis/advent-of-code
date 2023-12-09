data = [x.strip().split() for x in open("../_input/2023/day09.txt", "r").readlines()]
data = [[int(x) for x in line] for line in data]

one = 0
two = 0
for line in data:
    # make a list of sequential differences
    d = line
    p = [d]
    while any(d):
        d = [d[i + 1] - d[i] for i in range(len(d) - 1)]
        p.append(d)

    # backtrack, adding predicted value to each list
    p.reverse()
    for i, a in enumerate(p):
        if i != 0:
            a.append(p[i - 1][-1] + a[-1])
            a.insert(0, a[0] - p[i - 1][0])

    # target is the last value in the last list
    one += p[-1][-1]
    two += p[-1][0]
print(f"ONE: {one}")
print(f"TWO: {two}")
