#!/usr/bin/python

class Decor:
    def __init__(self):
        self.d = {'a':5, 'b':6}

    def __getitem__(self, key):
        return self.d[key]

    def __contains__(self, key):
        return key in self.d

d = Decor()
print(d['a'])
print('a' in d)