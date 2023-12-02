file = open('input.txt').read().split('\n')

num = 1
while len(file[num]) != 0:
    line = file[num].split(' ')
    if line[1] == 'cd':
        print(line)
    elif line[1] == 'ls':
        print(line)
        while len(file[num+1]) != 0 and file[num+1][0] != '$':
            next = file[num+1].split()
            if next[0] == 'dir':
                print(next)
            else:
                file = {'name': next[1], 'size': int(next[0])}
                print(file)
            num += 1
    else:
        raise RuntimeError("Bad")
    num += 1