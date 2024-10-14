#!/bin/sh

gcc -std=c++2a -Wall -Werror -o $1 $1.cpp -lstdc++ -lm
