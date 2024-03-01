#!/usr/bin/python3

import json
import argparse
from pyjsparser import parse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        print(parse(jsfile.read()))
