#!/usr/bin/python3
from collections import Counter

def numbers():
    for x in [1, 2, 1, 1, 2, -1, 3, 2]:
        if x > 0:
            yield x

for x in Counter(numbers()).items():
    print(x)

print('manual')
cnt = Counter()
cnt[1] += 1
cnt[2] += 2.5
cnt[1] += 3
cnt[3] += 8
print(cnt, cnt[2], cnt[3])
print(cnt.most_common())