# Fast prime number generator.

prime_gen is a utility to generate primes. It is based on the axiom that for any prime p > 6, p = 6k+1 or 6k-1.
### Fetch and build the software.
git clone the project to your machine. Run make from the root directory.
### Prerequisites
g++ ver 9.0
build-essentials
### Running the software
To run the software, in the git directory,

./prime_gen <exponent> -f <output file>
The exponent provides the range within which the primes are found.
  
If an output file is not present on the command line, prime_gen will print the number of primes in the given range and exit.

## Tests
To run the tests, 
cd tests
./test_all.sh
