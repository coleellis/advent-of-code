"""
--- Day 9: All in a Single Night ---
"""

from aocd import get_data

stream = get_data(day=9, year=2015).splitlines()
data = [x.split() for x in stream]

cities = set()
distances = {}
for a, _, b, _, d in data:
    cities.add(a)
    cities.add(b)
    distances[(a, b)] = int(d)
    distances[(b, a)] = int(d)


def min_recurse(city, visited):
    """Find the minimum distance to visit all cities"""
    if len(visited) == len(cities):
        return 0
    visited.add(city)
    return min(
        distances[(city, c)] + min_recurse(c, visited | {c}) for c in cities - visited
    )


def max_recurse(city, visited):
    """Find the maximum distance to visit all cities"""
    if len(visited) == len(cities):
        return 0
    visited.add(city)
    return max(
        distances[(city, c)] + max_recurse(c, visited | {c}) for c in cities - visited
    )


print("Part 1:", min(min_recurse(c, set()) for c in cities))
print("Part 2:", max(max_recurse(c, set()) for c in cities))
