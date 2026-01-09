# Fast prime number generator.

prime_gen is a utility to generate primes.   
It is based on the axiom that for any prime p > 4, p = 6k+1 or 6k-1.   
It uses trial division. For any number n, if n % d != 0 for all 5 < d < sqrt(n), then n is a prime.  

Running times for all primes under 10^10   
_chandra@falcon:prime_gen $ time ./prime_gen 10 -f out.10_  
_Generating first primes_  
_Done with first primes_  
_32000/32000_  
_total number of primes is 455052812_  
_real	4m55.524s_  
_user	157m5.744s_  
_sys	0m3.356s_  
Note: prime_gen is multithreaded.

## Other prime number finders.
There are a number of probablistic methods like miller rabin and pollard's rho. Both of them have trouble with squares.
Since division is an expensive operation, an approach to remove all multiples of known primes might be more appropriate.
## Build the software. 
git clone the project to your machine. Run make from the root directory.
## Prerequisites
Any linux/unix.  
g++ ver 9.0 or above.  
build-essentials or equivalent.
## Running the software (prime_gen)
To run the software, in the git directory,  
./prime_gen <exponent|max> -f output file.  
The exponent provides the range within which the primes are found. 
If 'max' is the second argument, primes upto 2^64 - 1 will be generated.
If an output file is not present on the command line, prime_gen will print the number of primes in the given range and exit.

## Tests
To run the tests,  
cd tests  
./test_all.sh
