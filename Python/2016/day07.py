"""
--- Day 7: Internet Protocol Version 7 ---
"""
import re
from aocd import get_data

stream = get_data(year=2016, day=7).splitlines()

ONE = sum(
    1
    for l in stream
    if re.search(r"(\w)(?!\1)(\w)\2\1", l)
    and not re.search(r"\[\w*(\w)(?!\1)(\w)\2\1\w*]", l)
)
print("Part 1:", ONE)

ssl = re.compile(r"(?=((.)(?!\2)(.)\2))")
hyp = re.compile(r"\[.*?\]")
TWO = sum(
    1
    for l in stream
    if [
        p
        for p in [
            (p1, f"{p1[1]}{p1[0]}{p1[1]}")
            for p1 in [m[0] for m in re.findall(ssl, l)]
            if f"{p1[0]}{p1[1]}{p1[0]}" in [m[0] for m in re.findall(ssl, l)]
        ]
        if p[0] in hyp.sub("|", l) and p[1] in "".join(re.findall(hyp, l))
    ]
)
print("Part 2:", TWO)
