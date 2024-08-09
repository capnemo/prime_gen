#!/usr/bin/python

import math
import random

def pollard_brent(n):
    if n % 2 == 0:
        return 2
    
    def gcd(a, b):
        while b:
            a, b = b, a % b
        return a

    def pollard_brent_helper(x0):
        y, c, m = random.randint(1, n-1), random.randint(1, n-1), random.randint(1, n-1)
        tortoise, hare, power, lam = x0, x0, 1, 1

        def f(x):
            return (pow(x, 2, n) + c) % n

        while True:
            if power == lam:
                t = 0
                for _ in range(min(m, power)):
                    hare = f(hare)
                    t = (t + 1) % m
                    if tortoise == hare:
                        return gcd(n, abs(tortoise - hare))

                lam *= 2
            tortoise = f(tortoise)
            hare = f(f(hare))
            power += 1

    x = random.randint(1, n-1)
    return pollard_brent_helper(x)

def factorize(n):
    factors = []
    while n > 1:
        factor = pollard_brent(n)
        factors.append(factor)
        n //= factor
    return factors

# Example usage:
#composite_number = 5959  # Replace with your composite number
#composite_number = 1000003 # Replace with your composite number
composite_number = 100000 # Replace with your composite number
result = factorize(composite_number)
print(f"Prime factors of {composite_number}: {result}")
