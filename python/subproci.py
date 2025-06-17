#!/usr/bin/python3

# Runs a 'cat' program as a subprocess and iterates with it

import os
import subprocess

msg = ['one', 'two', 'three']

if __name__ == '__main__':
    with subprocess.Popen(['cat'], stdin=subprocess.PIPE, stdout=subprocess.PIPE) as pcat:
        os.set_blocking(pcat.stdout.fileno(), False)
        for m in msg:
            pcat.stdin.write((m+'\n').encode())
            pcat.stdin.flush()
            print(pcat.stdout.read())
        pcat.stdin.close()
        pcat.wait()
        print(pcat.stdout.read())


