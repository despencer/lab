#!/usr/bin/python

class IterDemo:
    def __init__(self):
        self.data = [1, 2, 3, 4]

    def __iter__(self):
        return iter(self.data)

def someiter(data):
        for i in data:
            for j in IterDemo():
                yield i,j

for i in IterDemo():
    print(i)
for i in someiter(['a', 'b']):
    print(i)
for idx,i in enumerate(someiter(['a', 'b'])):
    print(idx, i)

print('list', list(someiter(['a', 'b','c'])))
