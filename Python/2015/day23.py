"""
--- Day 23: Opening the Turing Lock ---
"""
from aocd import get_data

stream = get_data(year=2015, day=23).splitlines()


def run(rr):
    """run the program with the given register values"""
    ip = 0
    while ip < len(stream):
        line = stream[ip]
        if line.startswith("hlf"):
            rr[line[4]] //= 2
            ip += 1
        elif line.startswith("tpl"):
            rr[line[4]] *= 3
            ip += 1
        elif line.startswith("inc"):
            rr[line[4]] += 1
            ip += 1
        elif line.startswith("jmp"):
            ip += int(line[4:])
        elif line.startswith("jie"):
            if rr[line[4]] % 2 == 0:
                ip += int(line[7:])
            else:
                ip += 1
        elif line.startswith("jio"):
            if rr[line[4]] == 1:
                ip += int(line[7:])
            else:
                ip += 1
        else:
            raise ValueError(f"Unknown instruction: {line}")
    return rr


print("Part 1:", run({"a": 0, "b": 0})["b"])
print("Part 2:", run({"a": 1, "b": 0})["b"])
