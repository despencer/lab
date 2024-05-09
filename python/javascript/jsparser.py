#!/usr/bin/python3

import json
import argparse
from pyjsparser import parse

def checknode(node, keys, nodetype = None):
    if nodetype != None and node['type'] != nodetype:
        raise Exception('Mismatched node type ' + node['type'] + ' (should be ' + nodetype + ')')
    if isinstance(keys, str):
        keys = [ keys ]
    keys.append('type')
    for k in node.keys():
        if k not in keys:
            raise Exception('Unknown key ' + k)

class Literal:
    def __init__(self, value, raw):
        self.value = value
        self.raw = raw

class Expression:
    @classmethod
    def load(cls, astnode):
        if astnode['type'] == 'Literal':
            checknode(astnode, ['value','raw'])
            return Literal( astnode['value'], astnode['raw'])
        else:
            raise Exception('Unknown expression type ' + astnode['type'])
        return None

class VariableDeclaration:
    def __init__(self):
        self.id = None
        self.kind = None
        self.expression = None

    @classmethod
    def load(cls, astnode, kind):
        checknode(astnode, ['id', 'init'], nodetype = 'VariableDeclarator')
        checknode(astnode['id'], 'name', nodetype='Identifier')
        vd = VariableDeclaration()
        vd.id = astnode['id']['name']
        vd.kind = kind
        if 'init' in astnode:
            vd.expression = Expression.load(astnode['init'])
        return vd

class Program:
    def __init__(self):
        self.vardecl = []

    @classmethod
    def load(cls, astnode):
        checknode(astnode, 'body')
        program = Program()
        for x in astnode['body']:
            if x['type'] == 'VariableDeclaration':
                checknode(x, ['declarations', 'kind'])
                for vd in x['declarations']:
                    program.vardecl.append( VariableDeclaration.load(vd, x['kind']) )
            else:
                raise Exception('Unknown type ' + x['type'])
        return program

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        ast = parse(jsfile.read());
        if ast['type'] != 'Program':
            print('Invalid AST')
        else:
            jscode = Program.load(ast)
