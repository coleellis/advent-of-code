from aocd import get_data

# stream = get_data(day=14, year=2022).splitlines()
stream = open("test.txt").read().splitlines()

data = [x.split('at ')[1:] for x in stream]

def coverage(y):
    for s in ss:
        print(s)

ss = set()
bb = set()
for a,b in data:
    lhs = [int(x.split('=')[1]) for x in a.split(':')[0].split(',')]
    rhs = [int(x.split('=')[1]) for x in b.split(',')]
    ss.add(tuple(lhs))
    bb.add(tuple(rhs))

print(ss)
print(bb)

print("Part 1:", coverage(10))