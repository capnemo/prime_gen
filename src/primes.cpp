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
    ulong p1,p2;
    if (((range_begin - 1) % 6) == 0) {
        if (is_prime(range_begin) == true)
            plist->push_back(range_begin);
        p1 = range_begin - 1 + 6 - 1;
        p2 = p1 + 2;       
    } else if (((range_begin) % 6) == 0) {
        if (is_prime(range_begin + 1) == true)
            plist->push_back(range_begin + 1);
        p1 = range_begin + 6 - 1;
        p2 = p1 + 2;
    } else {
        uint8_t rem = range_begin % 6;
        p1 = range_begin - rem + 6 - 1;
        p2 = p1 + 2;
    }
        
    while (p2 <= range_end) {
        if (is_prime(p1) == true)
            plist->push_back(p1);
        if (is_prime(p2) == true)
            plist->push_back(p2);
        p1 += 6;
        p2 = p1 + 2;
    }

    if ((p1 <= range_end) && (is_prime(p1) == true))
        plist->push_back(p1);
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

bool primes::find_primes_from_seeds(uint64_t num, ulong_vec& first_primes)
{
    uint64_t limit = sqrt(num);
    uint64_t n = 2; //Ignore 2 and 3.
    
    while (first_primes[n] <= limit) {
        if (num % first_primes[n] == 0)
            return false;
        n++;
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
    uint64_t p1 = 11;
    uint64_t p2 = 13;
    while (p2 <= limit) {
        if (find_primes_from_seeds(p1, first_primes) == true) 
            first_primes.push_back(p1);

        if (find_primes_from_seeds(p2, first_primes) == true) 
            first_primes.push_back(p2);

        p1 += 6;
        p2 += 6;
    }
}

/*
 * Returns the total number of primes calculated by this object.
 */
ulong primes::get_prime_count()
{
    return total_primes;
}

