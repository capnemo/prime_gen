#!/usr/bin/python

ser = 0
for t in range(1, 50):
    m6 = t*6 - 1
    p6 = t*6 + 1
    print(t, m6, m6*5, m6 % 6)
    print(t, p6, p6*5, p6 % 6)
