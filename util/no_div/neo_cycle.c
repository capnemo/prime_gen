/*
The idea here is to eliminate all multiples of known primes so only
primes remain.
The main data structure is an array of size input_size/3. All members of the
array are in ascending order and are of the form 6k +/- 1 for all 
k < input_size/3.

There are two cycles of multiples of a given prime.
if p is a prime then the closest multiples are p + p6/6 and p - p6/6
where p6 is the closest multiple of 6. Both cycles repeat themselves at
intervals of 2 * p (r).
Therefore, the multiples are 

(p - p6/6) + 1 * r and (p + p6) + 1 * r  
(p - p6/6) + 2 * r and (p + p6) + 2 * r  
(p - p6/6) + 3 * r and (p + p6) + 3 * r  
(p - p6/6) + 4 * r and (p + p6) + 4 * r  
.
.
.
.

To access an element in the array, the formula is
if x is the index, the value in the location pointed to by x is
3(x + 2) - 1 - (x % 2)
For ex, 7 ==> 25
        8 ==> 29
        0 ==> 5
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

typedef uint64_t u64;
u64* allocate_and_fill(u64 sz)
{
    u64* arr = (u64 *)malloc(sz * sizeof(u64));
    
    if (arr == 0) 
        return nullptr;

    u64 num = 5;
    u64 ix = 0;
    while (num < (sz * 3)) {
        arr[ix++] = num;
        arr[ix++] = num + 2;
        num += 6;
    }

    if (ix < sz) 
        arr[ix] = num;

    return arr;
}

void print_array(u64* arr, u64 sz)
{
    for(int i = 0;i < sz; i++) 
        printf("%lu\n", arr[i]);
}

void print_primes(u64* arr, u64 sz)
{
    for(int i = 0;i < sz; i++) 
        if (arr[i] != 0)
            printf("%lu\n", arr[i]);
}

void filter_multiples(u64 in, u64 lst_sz, u64* mlist)
{
    u64 m = mlist[in];
    if (m == 0)
        return;

    u64 f6 = (in % 2 == 0) ? (m + 1)/6:(m - 1)/6;
/*
    For an analytical proof, treat the following assignments as equations.
    w1 and w2 are the locations of multiples of m.
    m has a relationship with f6.
    f6 is a multiple of 6
*/
    u64 w1,w2;
    if (f6 * 6 > m) {
        w1 = 2 * (m - f6) - 1;
        w2 = 2 * (m + f6) - 2;
    } else {
        w1 = 2 * (m - f6) - 2;
        w2 = 2 * (m + f6) - 1;
    }

    u64 p = 2 * m;
    while (w2 < lst_sz) {
        mlist[w1] = 0;
        mlist[w2] = 0;
        w1 += p;
        w2 += p;
    }

    while (w1 < lst_sz) {
        mlist[w1] = 0;
        w1 += p;
    }
}

u64 get_list_length(u64 input_size)
{
    int p = (input_size % 6 == 5) ? 1:0;
    return (input_size + p)/3;
}

void remove_non_primes(u64* list, u64 sz)
{
    u64 last_sq = sqrt(list[sz - 1]);

    u64 ix = 0;
    while (list[ix] <= last_sq)
        filter_multiples(ix++, sz, list);
}

u64 process_args(int arg_len, char* args[])
{
    if ((arg_len > 3) || (arg_len <= 1)) 
            return 0;
    
    if (arg_len == 2) 
        return strtoull(args[1], nullptr, 10);

    if (arg_len == 3) 
        if (strncmp(args[1], "-x", strlen("-x")) != 0) 
            return 0;

    return pow(10, strtoull(args[2], nullptr, 10));
}

int main(int argc, char* argv[])
{
    u64 limit = process_args(argc, argv);
    if (limit == 0) {
        printf("Error\n");
        return -1;
    }

    u64 list_sz = get_list_length(limit);
    u64* prime_list = allocate_and_fill(list_sz);
    if (prime_list == nullptr) {
        printf("Not enough memory\n");
        return -1;
    }

    fprintf(stderr, "%lu\n", prime_list[list_sz - 1]);
    remove_non_primes(prime_list, list_sz);
    fprintf(stderr, "%lu\n", prime_list[list_sz - 1]);
    print_primes(prime_list, list_sz);
    return 0;
}
