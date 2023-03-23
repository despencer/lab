#!/usr/bin/python3

class With:
    def __init__(self):
        print('init')

    def __enter__(self):
        print('enter')
        return self

    def __exit__(self, extype, exvalue, extrace):
        print('exit', extype, exvalue, extrace)

def open():
    return 4

print('-start')
with With() as w:
    a = 5
    print('first with')

print('-second')
with open() as w:
    a = 6
    print('second with')

print('-interim', a)

with With() as w:
    print('second with')
    z = 1 / 0


print('-quit', a)
