#!/usr/bin/python3

class Test:
    def __init__(self):
        pass


Test.value = 'a'
print(Test.value)

class Base:
    def __init__(self):
        print('init at Base')

    @classmethod
    def get(cls):
        print('get at Base')

    @classmethod
    def set(cls):
        print('set at Base')
        cls()


class Derived(Base):
    def __init__(self):
        print('init at Derived')

    @classmethod
    def get(cls):
        print('get at Derived')

Base.get()
Derived.get()
Base.set()
Derived.set()
