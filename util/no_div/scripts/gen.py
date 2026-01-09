#!/usr/bin/python

ser = 0
for t in range(1, 100):
    print(t,ser,t * 6 - 1)
    ser += 1
    print(t,ser,t * 6 + 1)
    ser += 1
