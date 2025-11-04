#This is basically unmitigated rubbish. Takes too much time.
#Not worth the effort or time to investigate

#!/usr/bin/python
import sys

def gcd(a,b):
    while b != 0:
        t = b
        b = a % b
        a = t
    return a

def rho(num):
    x = 2
    y = x
    d = 1
    it = 0
    while d == 1:
        x = x*x + 1
        yp = y*y + 1
        y = yp*yp + 1
        d = gcd(abs(x - y), num)
        it += 1
    if d == num:
        print("#", it)
        return -1
    else:
        return d

n = int(sys.argv[1])
if (rho(n) == -1):
    print(n, "is a prime")
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
