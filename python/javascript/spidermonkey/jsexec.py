#!/usr/bin/python3

import argparse
import spidermonkey

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        try:
            spidermonkey.execute(jsfile.read())
        except Exception as e:
            print('JS error', e)
