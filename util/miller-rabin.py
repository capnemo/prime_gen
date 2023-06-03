#!/usr/bin/python3
import sys
import os

def trailing_zeros(num):
    mask  = 1
    nz = 0;

    while (num & mask == 0):
        nz = nz + 1
        mask = mask << 1

    return nz

def miller_rabin_test(num):
    num_min_1 = num - 1
    tz = trailing_zeros(num_min_1)
    odd = num_min_1 >> tz
    
    rem = (1 << odd) % num
    if ((rem == 1) or (rem == (num - 1))):
        return True

    for n in range(1,tz):
        exp = odd * (1 << n)
        rem = (1 << exp) % num
        if (rem == (num - 1)):
            return True
        
    return False
    
if (len(sys.argv) != 2):
    print("Usage " + sys.argv[0] + " <number>")
    print("Prints all primes upto 10^'number'")
    os._exit(os.EX_OK)

limit = pow(10, int(sys.argv[1]));
limit = limit//6 + 1

for n in range(1,limit):
    m = n*6
    if (miller_rabin_test(m - 1) == True):
        print(str(m - 1))
    if (miller_rabin_test(m + 1) == True):
        print(str(m + 1))
