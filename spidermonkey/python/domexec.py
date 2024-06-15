#!/usr/bin/python3

import argparse
import sys
import os
sys.path.insert(1, os.path.expanduser('~/dev/web'))
sys.path.insert(1, os.path.expanduser('~/dev/web/smjs'))
import spidermonkey
import webhtml
import webdom

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Executes a javascript file inside browser environment')
    parser.add_argument('html', help='dom file')
    parser.add_argument('js', help='script file')
    args = parser.parse_args()
    with open(args.html) as htmlfile:
        dom = webhtml.parse(htmlfile.read())
        window = webdom.setupcontext(dom)
        with open(args.js) as jsfile:
            with spidermonkey.connect(window) as context:
                try:
                    context.execute(jsfile.read())
                except Exception as e:
                    print('JS error:', e)
