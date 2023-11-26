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

def usage(prog_name):
    print("Usage " + prog_name + " [-c] <number>")
    print("Prints all primes upto 10^'number'")
    print("With -c the program will print if the number is prime or not")
    os._exit(os.EX_USAGE)
    
def prime_range(upper_limit):
    limit = pow(10, int(upper_limit))
    limit = limit//6 + 1

    print("2")
    print("3")
    for n in range(1,limit):
        m = n*6
        if (miller_rabin_test(m - 1) == True):
            print(str(m - 1))
        if (miller_rabin_test(m + 1) == True):
            print(str(m + 1))

if __name__ == "__main__":
    num_args = len(sys.argv)
    if num_args != 2 and num_args != 3:
        usage(sys.argv[0])

    if num_args == 2:
        prime_range(sys.argv[1])
        os._exit(os.EX_OK)

    if num_args == 3:
        if sys.argv[1] == "-c":
            is_prime = miller_rabin_test(int(sys.argv[2]))
            if is_prime == True:
                print(sys.argv[2],"is a prime")
            else:
                print(sys.argv[2],"is not a prime")
        else:
            usage(sys.argv[0])
    
