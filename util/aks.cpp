#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using vec_64 = std::vector<uint64_t>;
using pair_64 = std::pair<uint64_t, uint64_t>;
using pair_64_bl = std::pair<uint64_t, bool>;
using pair_vec = std::vector<pair_64_bl>;

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
********************************************************
void generate_list(uint64_t inp)
{
    std::cout << "2\n3\n5\n";
    for (uint64_t i = 6 ; i < inp; i += 6) {
        uint64_t m = i - 1;
        uint64_t n = i + 1;
        if (m % 5 != 0) 
            if (test_number(m) == true)
                std::cout << m << std::endl;

        if (n % 5 != 0)
            if (test_number(n) == true)
                std::cout << n << std::endl;
    }
}

/*******************************************************
  Tests if inp is a prime or not.
  IN: inp number to be tested.
********************************************************
void test_single_input(uint64_t inp)
{
    if (test_number(inp) == true)
        std::cout << "prime" << std::endl;
    else
        std::cout << "not a prime" << std::endl;
}

/*******************************************************
  Tests if inp is a prime or not by generating bionomial 
  coefficients/
  IN: inp: number to be tested
  OUT: bool, if the number is prime or not.
********************************************************
bool test_number(uint64_t num)
{
    bool is_prime = true;
    uint64_t lim = (num + 1)/2;
    for (int i = 2; i <= lim; i++) { 
        pair_64 d = pair_64(num - 1 + 1, num);
        if (reduce(d, i) == false)  {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}

/*******************************************************
  Reduces the fraction and determines if the number 
  perfectly divides the bionomial coefficient.
  IN: numtor First and last of the numerators
  IN: den_end: last of the denominators
  OUT: bool, if the coefficient is reduced or not.
********************************************************
bool reduce(pair_64& numtor, uint64_t den_end)
{
    uint64_t st = numtor.first;
    pair_vec num_pair_vec;
    for (int i = numtor.first; i <= numtor.second; i++) 
        num_pair_vec.push_back({st++, false});

    for (uint64_t den = 2; den <= den_end; den++) {
        uint64_t rem = numtor.first % den;
        uint64_t t = (rem == 0) ? 0:(den - rem);
        while (t < num_pair_vec.size()) {
            if (num_pair_vec[t].second == false) {
                num_pair_vec[t].first = num_pair_vec[t].first / den;
                num_pair_vec[t].second = true;
                break;
            } else 
                t += den;
        }
    }
   
    return (!num_pair_vec[num_pair_vec.size() - 1].second);
}

/*******************************************************
Usage message
IN prog_name: name of the program.
********************************************************
void usage(const char* prog_name)
{
    std::cout << std::string(prog_name) + " [-l] <number>" << std::endl;
    std::cout << "if '-l' is the first argument, generates primes upto ";
    std::cout << "the given number" << std::endl;
    std::cout << "Otherwise tests the given number for primality" << std::endl;
}
