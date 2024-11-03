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

    @classmethod
    def show(cls, t):
        print(t)

print('Start')
klass = Base
klass.get()
klass.show('Base class call')
print('Indirect call')

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

class Base2:
    def __init__(self):
        self.a = 'aaa'

    def report(self):
        print(self.a)

class Derived2(Base2):
    def __init__(self):
        super().__init__()
        print(self.a)

    def change(self):
        self.a = 'bbb'

def hasfunc(instance, funcname):
    if hasattr(instance, funcname) and callable(getattr(instance, funcname)):
        print('instance has func', funcname)
        return True
    print('instance has not func', funcname)
    return False


b = Derived2()
b.change()
b.report()

hasfunc(b, 'change')
hasfunc(b, 'report')
hasfunc(b, 'a')
hasfunc(b, 'aa')

print('variables', vars(b))