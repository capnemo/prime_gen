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

#include "queue_dispatch.h"
#include "prime_types.h"
#include "file_writer.h"

/*
 * Class to calculate all primes between a certain range.  Expected to run
 * in its own thread.
 */
#ifndef PRIMES_H
#define PRIMES_H
class primes {
    public:
    primes(int id, queue_dispatch& d_q, ulong_vec& primes, 
           file_writer* wr = nullptr):
           th_id(id), ranges_source(d_q), prime_factors(primes), writer(wr) {}

    void static generate_first_primes(ulong limit, ulong_vec& first_primes);
    void fetch_ranges();
    ulong get_prime_count();

    private:
    bool is_prime(ulong num);
    void fill_primes(ulong range_begin, ulong range_end, ulong_vec* plist);

    int th_id;
    queue_dispatch& ranges_source;
    ulong_vec prime_factors;
    std::set<int> prime_mods = {1,3,7,9};
    file_writer* writer;
    ulong total_primes = 0;
};
#endif /*PRIMES_H*/
