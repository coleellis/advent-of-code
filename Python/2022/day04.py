from aocd import get_data


def contains(x, y):
    xx = [int(a) for a in x.split("-")]
    yy = [int(a) for a in y.split("-")]
    return all(z in range(xx[0], xx[1] + 1) for z in range(yy[0], yy[1] + 1)) or all(
        z in range(yy[0], yy[1] + 1) for z in range(xx[0], xx[1] + 1)
    )


def overlap(x, y):
    xx = [int(a) for a in x.split("-")]
    yy = [int(a) for a in y.split("-")]
    return any(z in range(xx[0], xx[1] + 1) for z in range(yy[0], yy[1] + 1)) or any(
        z in range(yy[0], yy[1] + 1) for z in range(xx[0], xx[1] + 1)
    )


lines = [x.split(",") for x in get_data(day=4, year=2022).split("\n")]

one = sum([1 for x in lines if contains(x[0], x[1])])
print("Part 1:", one)

two = sum([1 for x in lines if overlap(x[0], x[1])])
print("Part 2:", two)
