#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cstdint>

using vec_64 = std::vector<uint64_t>;
using pair_64 = std::pair<uint64_t, uint64_t>;
using pair_64_bl = std::pair<uint64_t, bool>;
using pair_vec = std::vector<pair_64_bl>;
using set_64i = std::set<uint64_t>;

bool reduce(pair_64& numtor, uint64_t den_end);
bool test_number(uint64_t num);
void test_single_input(uint64_t inp);
void generate_list(uint64_t inp);
void usage(const char* prog_name);

int main(int argc, char *argv[])
{
    if ((argc != 2) && (argc != 3)) {
        usage(argv[0]);
        return -1;
    }

    uint64_t t_num = std::strtoll(argv[argc - 1], nullptr, 10);
    if (argc == 3)  {
        if (std::string(argv[1]) == "-l") {
            generate_list(t_num);
        } else {
            usage(argv[0]);
            return -1;
        }
    }

    if (argc == 2)
        test_single_input(t_num);
}

/*******************************************************
  Generates all primes upto inp
  IN: inp: limit
********************************************************/
void generate_list(uint64_t inp)
{
    std::cout << "2\n3\n5\n";
    for (uint64_t i = 6 ; i < inp; i += 6) {
        uint64_t m = i - 1;
        uint64_t n = i + 1;

        if (test_number(m) == true)
            std::cout << m << std::endl;

        if (test_number(n) == true)
            std::cout << n << std::endl;
    }
}

/*******************************************************
  Tests if inp is a prime or not.
  IN: inp number to be tested.
********************************************************/
void test_single_input(uint64_t inp)
{
    if (test_number(inp) == true)
        std::cout << "prime" << std::endl;
    else
        std::cout << "not a prime" << std::endl;
}

/*******************************************************
  Reduces the list of numerators by finding a suitable 
  numerator to reduce
  IN/OUT: ntor: list of numerators
  IN: den: new denominator
********************************************************/
void reduce_and_add(set_64i& ntor, uint64_t den)
{
    set_64i::iterator lb = ntor.lower_bound(den);
    uint64_t se = *lb;
    if (se == den) {
        ntor.erase(lb);
        return;
    }
   
    uint64_t le = *(--ntor.end());
    uint64_t fe = ((se/den) + 1) * den;
    while (fe <= le) {
        if (ntor.find(fe) != ntor.end()) {
            ntor.erase(fe);
            ntor.insert(fe/se);
            return;
        }
        fe += den;
    }
}

/*******************************************************
  Tests if inp is a prime or not by generating bionomial 
  coefficients. If the number divides the all the 
  coefficients perfectly, it is a prime.
  IN: num: number to be tested
  OUT: bool, if the number is prime or not.
********************************************************/
bool test_number(uint64_t num)
{
    if ((num % 5) == 0) 
        return false;

    uint64_t lim = (num % 2 == 0) ? num/2:num/2 + 1;
    uint64_t prod = 1;
    set_64i nmtor, dntor;
    for (int i = 1; i <= lim; i++) {
        uint64_t n = num - i + 1;
        uint64_t d = i;
        if (n % d == 0)
            nmtor.insert(n/d);
        else {
            nmtor.insert(n);
            reduce_and_add(nmtor, d);
        }

        if (*(--nmtor.end()) != num)
            return false;
    }
    return true;
}

/*******************************************************
Usage message
IN prog_name: name of the program.
********************************************************/
void usage(const char* prog_name)
{
    std::cout << std::string(prog_name) + " [-l] <number>" << std::endl;
    std::cout << "if '-l' is the first argument, generates primes upto ";
    std::cout << "the given number" << std::endl;
    std::cout << "Otherwise tests the given number for primality" << std::endl;
}
