/*
chandra@falcon:pn_sieve $ time ./six_primes 1000000 > 1m.out
99.62267

real	0m0.563s
user	0m0.507s
sys	0m0.053s
chandra@falcon:pn_sieve $ time ./six_primes 10000000 > 10m.out
99.88119

real	0m17.388s
user	0m17.068s
sys	0m0.254s
chandra@falcon:pn_sieve $ time ./six_primes 100000000 > 100m.out
99.962569

real	9m27.950s
user	9m23.288s
sys	0m2.400s
chandra@falcon:pn_sieve $  
!!!
Tested for correctness upto 2200. 
Compile line: g++ -ggdb -Ofast six_primes.cpp -o six_primes
*/
#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <algorithm>
#include <cmath>

using u64 = uint64_t;
using vec_int = std::vector<u64>;
using set_int = std::set<u64>;

void generate_sixes(u64 last, vec_int& sixes);
void generate_multiples(const vec_int& sixes, u64 f, u64 last, set_int& mltp);
void filter_sixes(vec_int& sixes, const set_int& mltp);
u64 get_max_factor(u64 max_factor, const vec_int num_arr);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Error" << std::endl;
        return -1;
    }

    u64 lst = std::strtoull(argv[1], nullptr, 10);
    vec_int sxs;
    generate_sixes(lst, sxs);
    u64 last_six = sxs[sxs.size() - 1];
    vec_int factors(sxs.begin(), sxs.begin() + get_max_factor(lst, sxs));
    double pc;
    for (int i = 0; i < factors.size(); i++) {
        set_int mt;
        generate_multiples(sxs, factors[i], last_six, mt);
        filter_sixes(sxs, mt);
        pc = (i*100)/(double)factors.size();
        std::cerr << "\r" << pc;
        std::cerr.flush();
    }
    
    std::cerr << std::endl;
    sxs.insert(sxs.begin(), 5);
    sxs.insert(sxs.begin(), 3);
    sxs.insert(sxs.begin(), 2);
    for (auto m:sxs)
        std::cout << m << std::endl;
}

u64 get_max_factor(u64 max_factor, const vec_int num_arr)
{
    u64 upper_bound = static_cast<u64>(sqrt(max_factor) + 1);
    int i = 0;
    while (upper_bound > num_arr[i])
        i++;

    return i;
}

void generate_sixes(u64 last, vec_int& sixes)
{
    u64 k = 6;
    int cycle = 0;
    while (k < last) {
        u64 sm = k - 1;
        u64 sp = k + 1;
        switch (cycle) {
            case 0:
            sixes.push_back(sp);
            cycle = 5;
            break;
            case 2:
            sixes.push_back(sm);
            break;
            default:
            sixes.push_back(sp);
            sixes.push_back(sm);
        }
        k += 6;
        cycle -= 1;
    }
}

void generate_multiples(const vec_int& sixes, u64 f, u64 last, set_int& mltp)
{
    for (int i = 0; i < sixes.size(); i++)  {
        u64 m = f * sixes[i];
        if (m > last)
            break;
        
        mltp.insert(m);
    }
}

void filter_sixes(vec_int& sixes, const set_int& mltp)
{
    std::set<u64> ss(sixes.begin(), sixes.end());
    vec_int::iterator it;

    it = std::set_difference(ss.begin(), ss.end(), mltp.begin(), mltp.end(), 
                             sixes.begin());
    sixes.resize(it - sixes.begin());
}
