#!/usr/bin/python3

import subprocess
import argparse
import os

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Runs a subprocess if arg is present')
    parser.add_argument('--next', action="store_true", required=False)
    args = parser.parse_args()
    print(os.getcwd(), os.path.abspath('.'), os.path.dirname(__file__))
    if args.next:
        res = subprocess.run([ __file__ ])


