"""
--- Day 6: Guard Gallivant ---
"""

from aocd import get_data

data = get_data(day=6, year=2024)

# Make grid
grid = [list(x) for x in data.splitlines()]
nr, nc = len(grid), len(grid[0])

# Get starting position
sx, sy = None, None
for row in range(nr):
    for col in range(nc):
        if grid[row][col] == "^":
            sx, sy = row, col

TWO = 0
for r in range(nr):
    for c in range(nc):
        # Where are we
        x, y = sx, sy
        DIRIDX = 0  # 0=up, 1=right, 2=down, 3=left

        # Sets
        ONESET = set()
        TWOSET = set()

        while True:
            # Have we seen this direction before? (P2)
            if (x, y, DIRIDX) in TWOSET:
                TWO += 1
                break

            # Add to seen list
            TWOSET.add((x, y, DIRIDX))
            ONESET.add((x, y))

            # Make movement
            dx, dy = [(-1, 0), (0, 1), (1, 0), (0, -1)][DIRIDX]
            xx = x + dx
            yy = y + dy

            # Did we escape? (P1)
            if not (0 <= xx < nr and 0 <= yy < nc):
                if grid[r][c] == "#":
                    ONE = len(ONESET)
                break

            # Check for turns
            if grid[xx][yy] == "#" or xx == r and yy == c:
                DIRIDX = (DIRIDX + 1) % 4
            else:
                x = xx
                y = yy

print("ONE:", ONE)
print("TWO:", TWO)
