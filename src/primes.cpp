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

#include "primes.h"

/*
 *  Fetches the prime number ranges from the dispatch queue, calculates
 *  the prime numbers in that range and sends them to the output thread.
 */
void primes::fetch_ranges()
{
    int iter = 0;
    range_desc rd;
    ranges_source.get_range(rd);
    
    while (rd.serial != -1) {
        ulong_vec* primes_list = new ulong_vec;
        fill_primes(rd.rbegin, rd.rend, primes_list);
        total_primes += primes_list->size();
        if (writer != nullptr)
            writer->add_buffer(rd.serial, primes_list);
        ranges_source.get_range(rd);
    }
}

/*
 *  Calculates prime numbers within an input range.
 *  in @range_begin  Range begin. 
 *  in @range_end    Range end.
 *  out @plist       Prime numbers in range.
 */
void primes::fill_primes(ulong range_begin, ulong range_end, ulong_vec* plist)
{
    ulong i = range_begin;
    while ((i <= range_end) && (i % 6 != 0)) {
        if (is_prime(i) == true)
            plist->push_back(i);
        i++;
    }

    while (i < range_end) {
        if (i + 1 > range_end)
            break;
        if (is_prime(i + 1) == true)
            plist->push_back(i + 1);

        if (i + 5 > range_end)
            break;
        if (is_prime(i + 5) == true)
            plist->push_back(i + 5);

        i += 6;
    }
}

/*
 * Checks if a number is a prime number.
 * in @num input number.
 */
bool primes::is_prime(ulong num) 
{

    if (num%10 == 5)
        return false;

    int i = 0;
    ulong prime_limit = sqrt(num) + 0.5;
    while (prime_factors[i] <= prime_limit) {
        if (num % prime_factors[i++] == 0)
            return false;
        if (i >= prime_factors.size())
            break;
    }
    return true;
}
/*
 * Calculates prime numbers upto a limit.
 *  in     @limit
 *  out    @first_primes 
 */
void primes::generate_first_primes(ulong limit, ulong_vec& first_primes)
{

    first_primes = ulong_vec({2,3,5,7});
    std::set<int> mods({0,2,3,4});
    for (int i = 10; i < limit; i++)  {
        int k = i % 6;
        if (mods.find(k) != mods.end())
            continue;
        int j = 0;
        bool is_prime = true;
        int prime_limit = sqrt(i) + 0.5;
        while (first_primes[j] <= prime_limit) {
            if (i % first_primes[j++] == 0) {
                is_prime = false;
                break;
            }
            if (j >= first_primes.size())
                break;
        }
        if (is_prime == true) 
            first_primes.push_back(i);
    }
}

/*
 * Returns the total number of primes calculated by this object.
 */
ulong primes::get_prime_count()
{
    return total_primes;
}

