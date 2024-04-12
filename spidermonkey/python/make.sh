#!/bin/sh

SM_INCLUDE=mozjs-102
SM_LIBRARY=mozjs-102
SM_INTERFACE="$HOME/dev/web/smjs"
PYTHON_INCLUDE=/usr/include/python3.11
WARNINGS="-Wno-invalid-offsetof -Wno-maybe-uninitialized"

gcc -I/usr/include/$SM_INCLUDE -I$PYTHON_INCLUDE -I$SM_INTERFACE -fPIC -Wall -std=c++2a -Werror $WARNINGS -shared -Wl,-soname,smjs.so -o smjs.so $SM_INTERFACE/smjspython.cpp $SM_INTERFACE/smjsvalues.cpp $SM_INTERFACE/smjs.cpp -l$SM_LIBRARY 2>&1 | tee make.log