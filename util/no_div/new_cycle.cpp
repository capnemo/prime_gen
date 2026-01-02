/*
This program uses 2 cycles to identify primes.
n is the number. 
nx6 is the nearest multiple of 6. p is +-1. 
nx6 = n + p.
Cycle 1:
The cycle is 6(n - n6/6) + p
=> 6(n - (n + p)/6) + p
=> 6n - n - p + p
=> 5n -- Multiple of n.
Cycle 2:
n * 6 + n -- Multiple of n.
=> 7n

The above needs elaboration. Look good, but is not useful.
-------------------------------------------------------------
chandra@falcon:no_div $ time ./new_cycle 1000000 > 1m.out

real	0m0.059s
user	0m0.026s
sys	0m0.033s
chandra@falcon:no_div $ time ./new_cycle 10000000 > 10m.out

real	0m0.486s
user	0m0.155s
sys	0m0.327s
chandra@falcon:no_div $ time ./new_cycle 100000000 > 100m.out

real	0m3.930s
user	0m1.349s
sys	0m2.558s
chandra@falcon:no_div $ time ./new_cycle 1000000000 > 1b.out

real	0m35.001s
user	0m12.030s
sys	0m22.851s
chandra@falcon:no_div $ time ./new_cycle 10000000000 > 10b.out

real	5m18.143s
user	1m48.038s
sys	3m29.143s
chandra@falcon:no_div $ 
*/

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using u64 = uint64_t;
using vec64 = std::vector<u64>;

struct cycle {
    u64 c1_st;
    u64 c2_st;
    u64 cl_sz;
};

u64 get_nearest_six(u64 num);
void calculate_sixes(vec64& sixes, u64 num_sixes);
void calculate_sixes(u64 start_six, u64 last_six, vec64& sixes);
void get_cycle(u64 num, cycle& num_cycle);
void print_list(vec64 v);
void filter_sixes(vec64& sixes);
u64 get_location(u64 num);
int get_six_difference(u64 num);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Error" << std::endl;
        return -1;
    }
    
    u64 last = std::strtoull(argv[1], nullptr, 10);
    if (last <= 18) {
        u64 exp_val = 1;
        for (int i = 0; i < last; i++) 
            exp_val *= 10;
        last = exp_val;
    }
    std::cout << "Limit is " << last << std::endl << std::flush;
    vec64 sxs;
    calculate_sixes(sxs, last);
    filter_sixes(sxs);
    print_list(sxs);
}

void get_cycle(u64 num, cycle& num_cycle)
{
    u64 n6 = get_nearest_six(num);
    num_cycle.c1_st = 6 * (num - n6/6) + get_six_difference(num);
    num_cycle.c2_st = num * 6 + num;
    num_cycle.cl_sz = 2 * num;
}

void filter_sixes(vec64& sixes)
{
    u64 sq_limit = static_cast<u64>(sqrt(sixes[sixes.size() - 1]));
    for (u64 i = 0; i < sq_limit; i++) {
        if (sixes[i] == 0) 
            continue;
        
        cycle cyc;
        get_cycle(sixes[i], cyc);
        u64 c1 = get_location(cyc.c1_st);
        u64 c2 = get_location(cyc.c2_st);
        while (c2 < sixes.size()) {
            sixes[c1] = 0;
            sixes[c2] = 0;
            c1 += cyc.cl_sz;
            c2 += cyc.cl_sz;
        }

        while (c1 < sixes.size()) {
            sixes[c1] = 0;
            c1 += cyc.cl_sz;
        }
    }

    vec64::iterator sx_it = std::remove_if(sixes.begin(), sixes.end(), 
                                           [](u64 n) { return n == 0;});
    sixes.erase(sx_it, sixes.end());
}

u64 get_location(u64 num)
{
    u64 n6 = get_nearest_six(num);
    u64 f3 = (n6/3) - 2;
    return (num < n6) ? f3:f3 + 1;
}

void calculate_sixes(vec64& sixes, u64 last_num)
{
    u64 current_six = 0;
    if (sixes.size() > 0) 
        current_six = sixes[sixes.size() - 1] - 1;

    current_six += 6;
    while (current_six < last_num) {
        sixes.push_back(current_six - 1);
        sixes.push_back(current_six + 1);
        current_six += 6;
    }
}

u64 get_nearest_six(u64 num)
{
    return ((num + 1) % 6 == 0) ? num + 1:num - 1;
}

int get_six_difference(u64 num)
{
    return ((num % 6) == 1) ? -1 : 1;
}

void print_list(vec64 v)
{
    auto f = [](const auto& n) {
        if (n != 0) 
            std::cout << n << std::endl;
    };

    for_each(v.begin(), v.end(),f);
}
