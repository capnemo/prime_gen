/*
chandra@falcon:cycles $ time ./prime_cycles 6 > 1m.out

real	0m0.061s
user	0m0.023s
sys	0m0.038s
chandra@falcon:cycles $ time ./prime_cycles 7 > 10m.out

real	0m0.474s
user	0m0.174s
sys	0m0.298s
chandra@falcon:cycles $ time ./prime_cycles 8 > 100m.out

real	0m4.098s
user	0m2.044s
sys	0m2.042s
chandra@falcon:cycles $ time ./prime_cycles 9 > 1b.out

real	0m37.710s
user	0m18.593s
sys	0m18.996s
chandra@falcon:cycles $ time ./prime_cycles 10 > 10b.out

real	5m50.307s
user	3m4.111s
sys	2m44.:00s
chandra@falcon:cycles $ 
*/

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cstdlib>

using u64 = uint64_t;
using vec64 = std::vector<u64>;

struct cycle {
    bool is_plus;
    u64  cycle_start;
    u64  cycle_one;
    u64  cycle_two;
    void print_cycle()
    {
        char sign = (is_plus == true) ? 'p':'m';
        std::cout << sign << "," << cycle_start << "," << cycle_one << "," 
                  << cycle_two << std::endl;
    }
};

u64 get_nearest_six(u64 num);
void calculate_sixes(vec64& sixes, u64 num_sixes);
void calculate_sixes(u64 start_six, u64 last_six, vec64& sixes);
void get_cycle(u64 num, cycle& num_cycle);
void print_list(vec64 v);
void filter_sixes(vec64& sixes);

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

void filter_sixes(vec64& sixes)
{
    for (u64 i = 0; i < sixes.size(); i++) {
        if (sixes[i] == 0) 
            continue;
        cycle cl;
        get_cycle(sixes[i], cl);
        int t1 = 1;
        int t2 = -1;
        int offset = -1;
        if (cl.is_plus == true) {
            offset = 0;
            t1 = -1;
            t2 = 1;
        }

        u64 w = cl.cycle_start * 2 + offset - 1;
        while (w < sixes.size()) {
            u64 m1 = w + 2 * cl.cycle_one + t1;
            u64 m2 = m1 + 2 * cl.cycle_two + t2;
            if (m1 > sixes.size() - 1)
                break;
            sixes[m1] = 0;
            if (m2 > sixes.size() - 1)
                break;
            sixes[m2] = 0;
            w = m2;
        }
    }

    vec64::iterator sx_it = std::remove_if(sixes.begin(), sixes.end(), 
                                           [](u64 n) { return n == 0;});
    sixes.erase(sx_it, sixes.end());
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

void get_cycle(u64 num, cycle& num_cycle)
{
    u64 n6 = get_nearest_six(num);
    u64 f6 = n6/6;
    
    num_cycle.is_plus = (num > n6) ? true:false;
    num_cycle.cycle_start = f6;
    num_cycle.cycle_one = num - (2 * f6);
    num_cycle.cycle_two = 2 * f6;
}

void print_list(vec64 v)
{
    for_each(v.begin(), v.end(), [](auto& n){std::cout << n << std::endl;});
}

void print_cycle_numbers()
{
    u64 last = 100;
    u64 k = 6;
    while (k < 100) {
        cycle cm,cp;
        std::cout << k - 1 << std::endl;
        get_cycle(k - 1, cm);
        cm.print_cycle();

        std::cout << k + 1 << std::endl;
        get_cycle(k + 1, cp);
        cp.print_cycle();
        k += 6;
    }
}
