#!/usr/bin/python

class IterDemo:
    def __init__(self):
        self.data = [1, 2, 3, 4]

    def __iter__(self):
        return iter(self.data)


for i in IterDemo():
    print(i)