#!/usr/bin/python3

import json
import argparse
import js2py

class Node:
    def __init__(self):
        pass

    def createElement(self, type):
        print('Create element', type)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        document = Node();
        context = js2py.EvalJs( {'document':document} )
        try:
            context.execute(jsfile.read())
        except Exception as e:
            print('JS error', e)
