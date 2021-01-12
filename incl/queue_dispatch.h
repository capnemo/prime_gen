#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <thread>
#include <mutex>
#include <queue>
#include <algorithm>

#include "prime_types.h"

/*
 * Class to move prime numbers from the prime number generator to a 
 * writer object.
 */
#ifndef QUEUE_DISPATCH_H
#define QUEUE_DISPATCH_H

class queue_dispatch {
    public:
    queue_dispatch(ulong min_p, ulong max_p, int n_th = 0):
                   first_prime(min_p), last_prime(max_p), 
                   num_threads(n_th) 
    {
        int exp = log10(last_prime) + 0.5;
        range_factor = (exp <= 8) ? 10: pow(10, exp - 8 + 1);
    }

    void fill_queue();
    void get_range(range_desc& range);
    int get_num_ranges();

    private:
    std::queue<struct range_desc> range_queue;
    std::mutex q_mutex;
    ulong first_prime;
    ulong last_prime;
    int range_factor = 10;
    int num_threads;
    int num_ranges = 0;
};

#endif /* QUEUE_DISPATCH_H */
