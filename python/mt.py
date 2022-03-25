#!/usr/bin/python3
import time
from datetime import datetime, timedelta
from threading import Thread

class Multi:
    def __init__(self):
        self.stop = False
    def countdown(self, n):
        self.start = datetime.now()
        while not self.stop and n > 0:
            delta = datetime.now()-self.start
            if delta > timedelta(seconds=5) :
                print(datetime.now())
                self.start = datetime.now()
            print('T-', n)
            n -= 1
            time.sleep(2)
        if n == 0:
            print("Finished")
        else:
            print("Stopped")

class Infinite:
    def __init__(self):
        pass

def countdown(n):
    while n > 0:
        print('T-', n)
        n -= 1
        time.sleep(2)

def single():
    try:
        countdown(10)
    except KeyboardInterrupt:
        print('Stopping')

def multi():
    print('Press enter to stop')
    m = Multi()
    t = Thread(target=m.countdown, args=(10,) )
    t.start()
    input()
    m.stop = True

multi()