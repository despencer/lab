#!/usr/bin/python3
from prettytable import PrettyTable
from prettytable import PLAIN_COLUMNS

x = PrettyTable()
x.field_names = ['Name', 'Age', 'Wealth']
x.add_row( [ 'eva.braun',15,'CORN:100'] )
x.add_row( [ 'john.arfield',5,'CORN:4'] )
x.align['Age']='r'
x.set_style(PLAIN_COLUMNS)
y = x.get_string(sortby='Age')
print(y)