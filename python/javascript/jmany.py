#!/usr/bin/python3

import js2py

context = js2py.EvalJs( {} )
context.execute('function fun() { return 5; }')
context.execute('var a = fun();')

