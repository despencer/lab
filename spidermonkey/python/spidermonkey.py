import smjs

class Context:
    def __init__(self):
        self.globals = {}

    def open(self):
        smjs.open_context(self)

    def close(self):
       smjs.close_context(self)

    def execute(self, jscode):
       smjs.execute(self, jscode)

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