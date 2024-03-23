#!/bin/sh

SM_INCLUDE=mozjs-102
SM_LIBRARY=mozjs-102
WARNINGS=-Wno-invalid-offsetof

gcc -I/usr/include/$SM_INCLUDE -fPIC -Wall -Werror $WARNINGS -shared -Wl,-soname,spidermonkey.so -o spidermonkey.so spidermonkey.cpp -l$SM_LIBRARY