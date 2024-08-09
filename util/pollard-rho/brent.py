#!/usr/bin/python
import sys

def gcd(a,b):
    while b != 0:
        t = b
        b = a % b
        a = t
    return a

def brent(num):
    x = 2
    y = x
    prod = 1
    it = 0
    for i in range(0, 99):
        x = (x*x + 1) % num
        yp = (y*y + 1) % num
        y = (yp*yp + 1) % num
        if x == y:
            break
        prod *= (abs(x - y))
        print(i, x, y, prod)

    return gcd(prod, num)

n = int(sys.argv[1])
print(brent(n))
"""
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
