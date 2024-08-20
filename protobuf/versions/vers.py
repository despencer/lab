#!/usr/bin/python3

import alpha_pb2
import beta_pb2
import gamma_pb2
import step1_pb2
import step2_pb2
import step3_pb2

def step1():
    data = step1_pb2.Data1()
    data.alpha.value = 4
    data.beta.value = 6
    print('Initialized', str(data).replace('\n',' '))
    print(data.SerializeToString())
    with open('./step1.data', 'wb') as f:
        f.write(data.SerializeToString())

def step2():
    with open('./step1.data', 'rb') as f:
        data = step2_pb2.Data2()
        data.ParseFromString(f.read())
    print('Load step 2', str(data).replace('\n',' '))
    data.gamma.value = 14
    print('Initialized step 2', str(data).replace('\n',' '))
    print(data.SerializeToString())
    with open('./step2.data', 'wb') as f:
        f.write(data.SerializeToString())

def step3():
    with open('./step2.data', 'rb') as f:
        data = step3_pb2.Data3()
        data.ParseFromString(f.read())
    print('Load step 3', str(data).replace('\n',' '))


def main():
    step1()
    step2()
    step3()

if __name__ == '__main__':
    main()