#!/usr/bin/python3

import argparse
import spidermonkey

class Document:
    def __init__(self):
        self.name = 'Name'

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        document = Document()
        with spidermonkey.connect() as context:
            try:
                context.add( {'print':print} )
                context.execute(jsfile.read())
            except Exception as e:
                print('JS error:', e)
