#!/usr/bin/python3

import sys
import os
sys.path.insert(1, os.path.expanduser('~/dev/softeng/javascript'))
import jsparser

def modify(jsprog):
    rules = jsparser.Rules()
    call = jsprog.body.statements[0]
    main = call.args.args[1]
    main.kind = jsparser.Function.declaration
    main.name = 'main'
#    main.body.top = True
#    print(main.body.pretty(rules))
    print(main.pretty(rules))
    print('main(window);\n')

if __name__ == '__main__':
    with open('jquery.slim.js') as jsfile:
        jsprog = jsparser.load(jsfile.read())
        modify(jsprog)
