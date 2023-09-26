#!/bin/sh

gcc -fPIC -Wall -Werror -shared -Wl,-soname,double.so -o double.so double.cpp