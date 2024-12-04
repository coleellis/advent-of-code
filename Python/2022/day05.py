"""
--- Day 5: Supply Stacks ---
"""

from aocd import get_data

raw_data = get_data(day=5, year=2022).split("\n")

# Strip the lines
strip_data = []
for item in raw_data:
    strip_data.append(item.strip())

# Get the line with the indices
BOTTOM = 0
for idx in range(len(strip_data)):
    if not strip_data[idx + 1]:
        BOTTOM = idx
        break

# Get num stacks
num_stacks = int(strip_data[BOTTOM].split(" ")[-1])

# Now read through the first 8 and start appending
stacks = [[] for _ in range(num_stacks)]
for line in range(BOTTOM):
    for loc, char in enumerate(strip_data[line]):
        if char not in ["[", "]", " "]:
            stacks[int(loc / 4)].append(char)

# Reverse all the lists
for item in stacks:
    item = item.reverse()

# Parse the rest of the lines
for line in range(num_stacks + 1, len(strip_data)):
    # Get the important values
    split = strip_data[line].split(" ")
    t = [int(split[1]), int(split[3]), int(split[5])]

    # Perform the action
    for move in range(t[0]):
        stacks[t[2] - 1].append(stacks[t[1] - 1][-1])
        stacks[t[1] - 1].pop()

# Print out the tops of the stacks
for item in stacks:
    print(item[-1], end="")
print()
