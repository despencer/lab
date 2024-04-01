import smjs

class Context:
    def __init__(self):
        self.jsglobals = {}

    def open(self):
        smjs.open_context(self)

    def close(self):
       smjs.close_context(self)

    def execute(self, jscode):
       smjs.execute(self, jscode)

    def add(self, globs):
       for name, obj in globs.items():
            self.jsglobals[name] = obj
            smjs.add_globalfunction(self, name)

    def funccall(self, funcname, args):
       self.jsglobals[funcname](*args)

    def __enter__(self):
        self.open()
        return self

    def __exit__(self, extype, exvalue, extrace):
        self.close()

def connect():
    return Context()

def shutdown():
    smjs.shutdown()

import atexit
atexit.register(shutdown)