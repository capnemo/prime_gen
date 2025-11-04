#!/usr/bin/python
import sys
import time

def fetch_primes(prime_file):
    pf = open(prime_file)
    pl = [ int(n_str) for n_str in pf ]

    return pl

def lucas_lehmer(exp):
    
    mp = 2**exp - 1
    s = 4
    for _ in range(1, exp - 1):
        s = (s*s - 2) % mp

    return True if s == 0 else False

if len(sys.argv) != 2:
    print('Error')
    sys.exit(-1)

prime_list = fetch_primes(sys.argv[1])

for p in prime_list:
    print(p, lucas_lehmer(p), time.time())
    sys.stdout.flush()
