#!/usr/bin/python
import sys

def gcd(a,b):
    while b != 0:
        t = b
        b = a % b
        a = t
    return a

def g_func(n, m):
    return ((n * n) + 1) % m

def rho(num):
    x = 2
    y = x
    d = 1
    it = 0
    while d == 1:
        print('AAA', x,y)
        x = g_func(x, num)
        y = g_func(g_func(y, num), num)
        d = gcd(abs(x - y), num)
        it += 1
        print('BBB', x,y)

    if d == num:
        return -1
    else:
        return d

n = int(sys.argv[1])
f = rho(n)
if (f == -1):
    print(n, "is a prime")
else:
    print(f, "is a factor")

"""
n = int(sys.argv[1])
for i in range(4, n):
    if i % 2 == 0:
        continue
    if (rho(i) == -1):
        print(i, "is a prime")
--------------------------------------
n = int(sys.argv[1])
n = n // 6 + 1
for i in range(1,n):
    j = 6*i - 1
    if rho(j) == -1:
        print(j)
    j += 2
    if rho(j) == -1:
        print(j)
    r = rho(j)
"""
