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

class Operand:
    literal = 1
    identifier = 2

    def __init__(self, kind, value, raw):
        self.kind = kind
        self.value = value
        self.raw = raw

    def pretty(self, rules):
        return self.raw

class Function:
    def __init__(self, name, decl):
        self.name = name
        self.decl = decl

    def pretty(self, rules):
        buf = 'function'
        if self.name != None:
            buf += ' ' + self.name
        if not self.decl:
            buf = '(' + buf + ')'
        return buf

    @classmethod
    def load(cls, astnode, decl):
        checknode(astnode, ['id','params','defaults','body','generator','expression'])
        checknode(astnode['id'], 'name')
        if astnode['generator'] or astnode['expression']:
            raise Exception('Generators or expressions are not yet implemented')
        return Function(astnode['id']['name'], decl)

class Call:
    def __init__(self, callee):
        self.callee = callee
        self.args = []

    def pretty(self, rules):
        return self.callee.pretty(rules) + '(' + ','.join( map(lambda x: x.pretty(rules), self.args) ) + ');'

    @classmethod
    def load(cls, astnode):
        checknode(astnode, ['callee','arguments'] )
        call = Call(Expression.load(astnode['callee']))
        for a in astnode['arguments']:
            call.args.append( Expression.load(a) )
        return call

class Expression:
    def pretty(self, rules):
        return ''

    @classmethod
    def load(cls, astnode):
        if astnode['type'] == 'Literal':
            checknode(astnode, ['value','raw'])
            return Operand(Operand.literal, astnode['value'], astnode['raw'])
        elif astnode['type'] == 'CallExpression':
            return Call.load(astnode)
        elif astnode['type'] == 'FunctionExpression':
            return Function.load(astnode, false)
        elif astnode['type'] == 'Identifier':
            checknode(astnode, 'name')
            return Operand(Operand.identifier, astnode['name'], astnode['name'])
        else:
            raise Exception('Unknown expression type ' + astnode['type'])
        return None

class VariableDeclaration:
    def __init__(self):
        self.id = None
        self.kind = None
        self.expression = None

    def pretty(self, rules):
        buf = self.kind + ' ' + self.id
        if self.expression != None:
            buf += ' = ' + self.expression.pretty(rules)
        buf += ';'
        return buf

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
        self.exprs = []
        self.funcs = []
        self.body = []

    def pretty(self, rules):
        buf = ""
        for v in self.body:
            buf += v.pretty(rules) + '\n'
        return buf

    @classmethod
    def load(cls, astnode):
        checknode(astnode, 'body')
        program = Program()
        for x in astnode['body']:
            if x['type'] == 'VariableDeclaration':
                checknode(x, ['declarations', 'kind'])
                for vdn in x['declarations']:
                    vd = VariableDeclaration.load(vdn, x['kind'])
                    program.vardecl.append(vd)
                    program.body.append(vd)
            elif x['type'] == 'ExpressionStatement':
                checknode(x, 'expression')
                ex = Expression.load(x['expression'])
                program.exprs.append(ex)
                program.body.append(ex)
            elif x['type'] == 'FunctionDeclaration':
                fn = Function.load(x, True)
                program.funcs.append(fn)
                program.body.append(fn)
            elif x['type'] == 'EmptyStatement':
                checknode(x, [])
                ex = Expression()
                program.exprs.append(ex)
                program.body.append(ex)
            else:
                raise Exception('Unknown type ' + x['type'])
        return program

def load(jssource):
    ast = parse(jssource);
    if ast['type'] != 'Program':
        raise Exception('Invalid AST ' + ast['type'])
    else:
        return Program.load(ast)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Reads a javascript file')
    parser.add_argument('js', help='a js file')
    args = parser.parse_args()
    with open(args.js) as jsfile:
        load(jsfile.read())
