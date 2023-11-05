#!/usr/bin/python3
import os

filename = '~/dev/lab/python/files.py'
filename = os.path.expanduser(filename)
print(filename)
filedir = os.path.dirname(filename)
filebase = os.path.basename(filename)
print(filedir, filebase)