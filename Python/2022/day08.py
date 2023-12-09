"""
--- Day 8: Treetop Tree House ---
"""
import numpy as np
from aocd import get_data

stream = get_data(day=14, year=2022)

lines = [l.strip() for l in stream.split("\n")]

trees = np.zeros((len(lines), len(lines[0])), dtype=int)
for i, line in enumerate(lines):
    trees[i, :] = np.array(list(line))

# the edges are always visible
visible_trees = 2 * len(lines[0]) + 2 * (len(lines) - 2)

# iterate over trees
for i in range(1, trees.shape[0] - 1):
    for j in range(1, trees.shape[1] - 1):
        tree_column = trees[:, j] - trees[i, j]
        tree_row = trees[i, :] - trees[i, j]
        routes = [
            tree_row[:j],
            tree_row[j + 1 :],
            tree_column[:i],
            tree_column[i + 1 :],
        ]
        if sum(list(map(lambda route: (route < 0).all(), routes))) > 0:
            visible_trees += 1
print(visible_trees)

scenic_scores = np.zeros((len(lines), len(lines[0])), dtype=int)


def compute_scenic_score(route):
    """Returns the scenic score of a route"""
    big_trees_array = list(route >= 0)
    if True in big_trees_array:
        return big_trees_array.index(True) + 1
    else:
        return len(big_trees_array)


# iterate over trees
for i in range(1, trees.shape[0] - 1):
    for j in range(1, trees.shape[1] - 1):
        tree_column = trees[:, j] - trees[i, j]
        tree_row = trees[i, :] - trees[i, j]
        # left, right, up, down
        routes = [
            tree_row[j - 1 :: -1],
            tree_row[j + 1 :],
            tree_column[i - 1 :: -1],
            tree_column[i + 1 :],
        ]
        scenic_scores[i, j] = np.prod(list(map(compute_scenic_score, routes)))

print(np.max(scenic_scores))
