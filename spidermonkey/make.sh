#!/bin/sh

SM_INCLUDE=mozjs-102
SM_LIBRARY=mozjs-102
SM_INTERFACE="$HOME/dev/web/smjs"
WARNINGS="-Wno-invalid-offsetof -Wno-maybe-uninitialized"
NAME=$1

gcc -I/usr/include/$SM_INCLUDE -I$SM_INTERFACE -fPIC -Wall -Werror $WARNINGS -o $NAME $NAME.cpp $SM_INTERFACE/smjs.cpp -l$SM_LIBRARY -lstdc++
