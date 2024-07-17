#!/usr/bin/python3

import argparse
import bs4

def pretty(node, pad):
    content = ''
    if isinstance(node, bs4.Tag):
        content = node.name
    if isinstance(node, bs4.NavigableString):
        content = str(node)
    print(''.ljust(pad), node.__class__.__name__, content)
    if hasattr(node, 'contents'):
        for n in node.contents:
            pretty(n, pad+4)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Load an html file')
    parser.add_argument('html', help='dom file')
    args = parser.parse_args()
    with open(args.html) as htmlfile:
        soup = bs4.BeautifulSoup(htmlfile, 'html5lib')
        pretty(soup, 0)
