data = open('input.txt', 'r').readlines()

items = []
times = data[0].split(':')[1].strip().split(' ')
times = list(filter(lambda x: x != '', times))
dists = data[1].split(':')[1].strip().split(' ')
dists = list(filter(lambda x: x != '', dists))
for i in range(len(times)):
    items.append((int(times[i]), int(dists[i])))

# Part 1
one = 1
ways = 0
for item in items:
    time, dist = item
    for t in range(time):
        if t * (time - t) > dist:
            ways += 1
    one *= ways
    ways = 0

print("ONE:", one)

# Part 2
time = int(''.join(map(str, times)))
dist = int(''.join(map(str, dists)))

two = 0
for t in range(time):
    if t * (time - t) > dist:
        two += 1

print("TWO:", two)
