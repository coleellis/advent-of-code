from functools import reduce

data = open("../_input/2023/day06.txt", "r").readlines()
times = list(map(int, data[0].split(":")[1].strip().split()))
dists = list(map(int, data[1].split(":")[1].strip().split()))


def win(t, d):
    return sum(1 for i in range(t) if i * (t - i) > d)


one = reduce(lambda x, y: x * y, map(win, times, dists))
print("ONE:", one)

time = int("".join(map(str, times)))
dist = int("".join(map(str, dists)))

two = sum(1 for i in range(time) if i * (time - i) > dist)
print("TWO:", two)
