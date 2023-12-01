with open('input.txt', 'r') as f:
    raw_data = f.readlines()

# strip the lines
strip_data = []
for item in raw_data:
    strip_data.append(item.strip())

# get the line with the indices
bottom = 0
for idx in range(len(strip_data)):
    if not strip_data[idx + 1]:
        bottom = idx
        break

# get num stacks
num_stacks = int(strip_data[bottom].split(' ')[-1])

# now read through the first 8 and start appending
stacks = [[] for x in range(num_stacks)]
for line in range(bottom):
    for loc, char in enumerate(strip_data[line]):
        if char not in ['[', ']', ' ']:
            stacks[int(loc / 4)].append(char)

# reverse all the lists
for item in stacks:
    item = item.reverse()

# parse the rest of the lines
for line in range(num_stacks + 1, len(strip_data)):
    # get the important values
    split = strip_data[line].split(' ')
    tuple = [int(split[1]), int(split[3]), int(split[5])]

    # perform the action
    for move in range(tuple[0]):
        stacks[tuple[2]-1].append(stacks[tuple[1]-1][-1])
        stacks[tuple[1]-1].pop()

# print out the tops of the stacks
for item in stacks:
    print(item[-1], end='')
print()
