#!/usr/bin/python3

import pandas as pd

df = pd.DataFrame({'c1':['a','b','c'], 'c2':[1,2,3]})
print(df.to_string())
for index, row in df.iterrows():
    print("index='{0}', row='{1}','{2}'".format(index, row['c1'], row['c2']))
for index, row in df.iterrows():
    df.loc[index, 'c3'] = row['c1']+str(row['c2'])
print(df.to_string())

print('concat')
df = pd.concat([df, pd.DataFrame({'c1':['d','e','f'], 'c2':[4,5,6]})], ignore_index=True, sort=False )
print(df)

df = pd.DataFrame({'c1':[112/3,112/6,112/12], 'c2':[1,2,3]})
print(df.to_string(formatters = {'c1':lambda x: "{:6.4f}".format(x)} ))
print("Min {0} Max {1}".format(df['c2'].min(), df['c2'].max()))

df = pd.DataFrame({'d1':['a','b','c'], 'd2':[None,None,None]})
print(df.to_string())
print("Min {0} Max {1} Check {2}".format(df['d2'].min(), df['d2'].max(), pd.isna(df['d2'].max())))

df = pd.DataFrame({'d1':['a','b','c'], 'd2':[None,4,None]})
print(df.to_string())
print("Min {0} Max {1} Check {2}".format(df['d2'].min(), df['d2'].max(), pd.isna(df['d2'].max())))