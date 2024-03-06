#!/bin/sh

gcc -fPIC -Wall -Werror -shared -Wl,-soname,spidermonkey.so -o spidermonkey.so spidermonkey.cpp