import collections

lines = [i.strip() for i in open('day07.txt').readlines()]

def one(h):
    h2 = ['J23456789TXQKA'.index(i) for i in h]
    p = tuple(sorted(collections.Counter(h).values()))
    t = [(1, 1, 1, 1, 1), (1, 1, 1, 2), (1, 2, 2), (1, 1, 3), (2, 3), (1, 4), (5,)].index(p)
    return t, *h2

def two(h):
    h2 = ['J23456789TXQKA'.index(i) for i in h]
    l = []
    for c in 'J23456789TQKA':
        l.append(one(h.replace('J', c)))
    return max(l)[0], *h2

first = sorted((one(h.replace('J', 'X')), int(b)) for h, b in (l.split() for l in lines))
f = sum(i*b+b for i,(_,b) in enumerate(first))
print('ONE:', f)

second = sorted((two(h), int(b)) for h, b in (l.split() for l in lines))
s = sum(i*b+b for i,(_,b) in enumerate(second))
print('TWO:', s)