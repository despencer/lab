#!/usr/bin/python3

class With:
    def __init__(self):
        print('init')

    def __enter__(self):
        print('enter')
        return self

    def __exit__(self, extype, exvalue, extrace):
        print('exit')

print('start')
with With() as w:
    print('first with')

print('interim')

with With() as w:
    print('second with')
    z = 1 / 0

print('quit')
