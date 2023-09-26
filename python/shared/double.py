#!/usr/bin/python3

import ctypes

libdouble = ctypes.CDLL('./double.so')
doublebuf = libdouble.doublebuf

buf = ctypes.create_string_buffer(bytes([1,2,3,4,11,12,13,14]))
print(buf.raw)
doublebuf(buf, 8)
print(buf.raw)
