#!/usr/bin/python3

class B1:
    def __init__(self, value):
        print('B1 init')
        self.b1 = value

    def one(self):
        print('one ', self.b1)

class B2:
    def __init__(self, value):
        print('B2 init')
        self.b2 = value

    def two(self):
        print('two ', self.b2)

class B11(B1):
    def __init__(self):
        print('B11 init')
        B1.__init__(self, 'a')
        self.b11 = 'c'

class B12bad(B1, B2):
    def __init__(self):
        print('B11 init')
        B1.__init__(self, 'a12')
        self.b12 = 'c12'

class B12(B1, B2):
    def __init__(self):
        print('B11 init')
        B1.__init__(self, 'a1-12')
        B2.__init__(self, 'a2-12')
        self.b12 = 'c12'

class B112(B12, B2):
    def __init__(self):
        print('B112 init')
        B12.__init__(self)
        B2.__init__(self, 'a122-12')
        self.b112 = 'c112'


b = B11()
print(b.b1, b.b11)
b12bad = B12bad()
b12 = B12()
print(b12.b1, b12.b2, b12.b12)
b12.one()
b12.two()

b112 = B112()
print(b112.b1, b112.b2, b112.b12)