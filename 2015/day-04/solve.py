import hashlib

input = 'ckczppom'
key = 0
while True:
    string = input + str(key)
    hash = hashlib.md5(string.encode()).digest().hex()
    if hash[0:6] == '000000':
        print(key)
        break
    key = key + 1