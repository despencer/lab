#!/usr/bin/python

class Some:
    def __init__(self, num):
        self.num = num

    def example(self):
        print(self.num)

func = Some.example
s = Some(4)
func(s)