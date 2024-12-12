# Advent of Code -- Python

Python is the primary language I used to code Advent mainly because it's easy to develop. As I've done more challenges and browsed solutions on the Reddit, I've learned plenty of new techniques on how to handle certain challenges. Most challenges can be done in very few lines.

This code is formatted using `black` which sometimes makes the code longer than it really is. Some challenges are as short as 8 lines for both parts, but `black` turns it into 20-something.

## Utilities

The primary utility here is `aocd` for importing the data. I prefer to submit the data manually, although I could probably get some faster times (a second or so) writing it automatically. `aocd.submit` is useful for some people, but I really only use `aocd.get_data`.

I've scored very well many days using `networkx`. However, this takes some challenge to build the graph itself. Once the graph is built, the rest of the solution is never more than about three lines. This yielded 8th place globally on [2023/25](./2023/day25.py). A 175-line [C solution](../C/2024/day10.c) and 350-line [Assembly Solution](../ASM/2024/day10.asm) becomes [8 lines](./2024/day10.py) using `networkx`.

Other good tools for parsing include `functools.cache`, `collections.deque` and `collections.defaultdict`, `itertools.product` and `itertools.permutations`, and `numpy`.
