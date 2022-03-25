#!/usr/bin/python3
from collections import Counter

def numbers():
    for x in [1, 2, 1, 1, 2, -1, 3, 2]:
        if x > 0:
            yield x

for x in Counter(numbers()).items():
    print(x)