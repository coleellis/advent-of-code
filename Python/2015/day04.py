"""
--- Day 4: The Ideal Stocking Stuffer ---
"""

import hashlib

SS = "ckczppom"
ONE = 0
while True:
    STRING = SS + str(ONE)
    HASH = hashlib.md5(STRING.encode()).digest().hex()
    if HASH[0:5] == "00000":
        print("Part 1:", ONE)
        break
    ONE = ONE + 1

TWO = 0
while True:
    STRING = SS + str(TWO)
    HASH = hashlib.md5(STRING.encode()).digest().hex()
    if HASH[0:6] == "000000":
        print("Part 2:", TWO)
        break
    TWO = TWO + 1
