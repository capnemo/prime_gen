#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using vec_64 = std::vector<uint64_t>;
using pair_64 = std::pair<uint64_t, uint64_t>;
using pair_64_bl = std::pair<uint64_t, bool>;
using pair_vec = std::vector<pair_64_bl>;

bool get_combinations(uint64_t num, uint64_t r);
bool reduce(pair_64& numtor, uint64_t den_end);
bool test_number(uint64_t num);

#if 0
int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "error" << std::endl;
        return -1;
    }

    std::cout << "2\n3\n5\n";
    uint64_t lim = std::strtoll(argv[1], nullptr, 10);
    for (uint64_t i = 6 ; i < lim; i += 6) {
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

#endif
int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "error" << std::endl;
        return -1;
    }

    uint64_t t_num = std::strtoll(argv[1], nullptr, 10);
    if (test_number(t_num) == true)
        std::cout << "prime" << std::endl;
    else
        std::cout << "not a prime" << std::endl;
}

bool test_number(uint64_t num)
{
    bool is_prime = true;
    uint64_t lim = (num + 2)/2;
    for (int i = 1; i <= lim; i++) { //start with 2.
        if (get_combinations(num, i) == false)  {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}

#if 0
bool test_number(uint64_t num)
{
    bool is_prime = true;
    uint64_t lim = (num + 2)/2;
    for (int i = 1; i <= lim; i++) {
        pair_64 combi_numtor(i + 1, num);
        if (reduce(combi_numtor, i) == false)  {
            is_prime = false;
            break;
        }
    }
    return is_prime;
}
#endif

bool get_combinations(uint64_t num, uint64_t r)
{
    uint64_t k = num - r;
    if (k >= r)  {
        pair_64 combis(k + 1, num);
        return reduce(combis, r);
    } else  {
        pair_64 combis(r + 1, num);
        return reduce(combis, k);
    }
}
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
                //num_pair_vec[t].first = num_pair_vec[t].first / den;
                num_pair_vec[t].second = true;
                break;
            } else 
                t += den;
        }
    }
   
    return (!num_pair_vec[num_pair_vec.size() - 1].second);
}
