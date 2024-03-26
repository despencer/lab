#!/bin/sh

SM_INCLUDE=mozjs-102
SM_LIBRARY=mozjs-102
PYTHON_INCLUDE=/usr/include/python3.11
WARNINGS=-Wno-invalid-offsetof

gcc -I/usr/include/$SM_INCLUDE -I$PYTHON_INCLUDE -fPIC -Wall -Werror $WARNINGS -shared -Wl,-soname,smjs.so -o smjs.so smjspython.cpp -l$SM_LIBRARY