#!/bin/sh

SM_INCLUDE=mozjs-102
SM_LIBRARY=mozjs-102
WARNINGS=-Wno-invalid-offsetof
NAME=hello

gcc -I/usr/include/$SM_INCLUDE -fPIC -Wall -Werror $WARNINGS -o $NAME $NAME.cpp smjs.cpp -l$SM_LIBRARY -lstdc++