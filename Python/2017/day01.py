"""
--- Day 01: Inverse Captcha ---
"""

from aocd import get_data

data = get_data(day=1, year=2017)

ONE = 0
num = data + data[0]
for a, b in zip(num, num[1:]):
    if a == b:
        ONE += int(a)
print("ONE:", ONE)

TWO = 0
for a, b in zip(data, data[len(data) // 2 :]):
    if a == b:
        TWO += int(a)
print("TWO:", TWO * 2)
