#!/usr/bin/python

class lazy1:
    def __init__(self, func):
        self.func = func

    def __get__(self, instance, cls):
        if instance is None:
            return self
        else:
            value = self.func(instance)
            setattr(instance, self.func.__name__, value)
            return value

class Lazy2:
    def __init__(self, name, func):
        self.func = func
        self.name = name

    def __get__(self, instance, cls):
        print('Lazy2')
        if instance is None:
            return self
        else:
            value = self.func(instance)
            setattr(instance, self.name, value)
            return value

def fcalc2(instance):
    print('calc2')
    return 2

def fcalc3(instance):
    print('calc3')
    return 3

class model:
    def __init__(self):
        pass

    @lazy1
    def calc1(self):
        print('calc1')
        return 1

c = model()
q = lambda value: setattr(value.__class__, 'calc3', Lazy2('calc3', fcalc3))
setattr(model, 'calc2', Lazy2('calc2', fcalc2) )
print('calc1A =', c.calc1)
print('calc1B =', c.calc1)
print('calc2A =', c.calc2)
print('calc2B =', c.calc2)
q(c)
print('calc3 =', c.calc3)

