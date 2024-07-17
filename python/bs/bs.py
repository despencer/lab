#!/usr/bin/python3

import argparse
from bs4 import BeautifulSoup

def main(soup):
    print(soup.__class__)
    print(soup.html.name)
    for a in soup.contents:
        print(a.__class__)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Load an html file')
    parser.add_argument('html', help='dom file')
    args = parser.parse_args()
    with open(args.html) as htmlfile:
        soup = BeautifulSoup(htmlfile, 'html5lib')
        main(soup)
