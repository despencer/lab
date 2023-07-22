#!/usr/bin/python3
import importlib

s = 'subdir'
m = 'plugin'

plugin = importlib.import_module(s + '.' + m)

def main():
    getattr(plugin, 'hello')()

main()
