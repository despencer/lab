#!/usr/bin/python

class Provider:
    @classmethod
    def extension(cls, self, name):
        print('from class', name, self.num)

class Some:
    def __init__(self, num):
        self.num = num

    def example(self):
        print(self.num)

    def exaparam(self, param):
        print(self.num+param)

    def getparam(self):
        return lambda x: self.exaparam(x)

    def getparam2(self):
        return self.exaparam

    def getparam3(self):
        ss = Some(11)
        return ss.exaparam

def extension(self, name):
    print('from function', name, self.num)

func = Some.example
s = Some(4)
func(s)

func2 = Some.exaparam
func2(s, 3)

func3 = lambda x: func2(s, x)
func3(4)

func4 = s.getparam()
func4(5)

func5 = s.getparam2()
func5(10)

func6 = s.getparam3()
func6(8)

setattr(s.__class__, 'ext', extension)
s.ext('aa')

setattr(s.__class__, 'ext', Provider.extension)
s.ext(s,'bb')

setattr(s.__class__, 'ext', lambda s,n: Provider.extension(s, n))
s.ext('cc')
