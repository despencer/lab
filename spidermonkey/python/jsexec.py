#!/usr/bin/python3

import argparse
import sys
import os
sys.path.insert(1, os.path.expanduser('~/dev/web/smjs'))
import spidermonkey

class Document:
    def __init__(self):
        self.name = 'A name'
        self.base = 'A base'

class HelloObject:
    def __init__(self):
        self.document = Document()

    def print(self, str):
        print(str)

    def hello(self):
        return 'Hello, world from Python!'

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        hello = HelloObject()
        document = Document()
        with spidermonkey.connect(hello) as context:
            try:
#                context.add( {'print':print, 'hello':hello} )
#                context.add( {'document':document} )
                context.execute(jsfile.read())
            except Exception as e:
                print('JS error:', e)
