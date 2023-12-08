from functools import reduce
from math import gcd

data = [x.strip() for x in open("../_input/2023/day08.txt", "r").readlines()]

def gen_tree(d):
    tree = {}
    for l, line in enumerate(d):
        if l < 2:
            continue
        line = line.split()
        tree[line[0]] = [line[2][1:-1], line[3][:-1]]
    return tree

repeater = data[0]
tree = gen_tree(data)

def parse(starts):
    n = {}
    i = 0
    while len(list(n.keys())) != len(starts):
        for k in range(len(starts)):
            if starts[k][-1] == 'Z':
                n[k] = i
            if repeater[i % len(repeater)] == 'R':
                starts[k] = tree[starts[k]][1]
            else:
                starts[k] = tree[starts[k]][0]
        i += 1
    return reduce(lambda x, y: x * y // gcd(x,y), list(n.values()))

print(f"ONE: {parse(['AAA'])}")
print(f"TWO: {parse([k for k in list(tree.keys()) if k[-1] == 'A'])}")
