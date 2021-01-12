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
/*
 * Calculated the ranges based on end range and the number of threads.
 */
void queue_dispatch::fill_queue()
{
    if (num_threads == 0)
        num_threads = std::thread::hardware_concurrency();
    num_ranges = num_threads * range_factor;
    ulong range_size = (last_prime - first_prime)/num_ranges;
    ulong range_begin = first_prime;
    ulong range_end = range_size;

    for (int i = 0; i < num_ranges; i++)  {
        if (i == num_ranges - 1)
            range_end = last_prime;
        range_queue.push({i, range_begin, range_end});
        range_begin = range_end + 1;
        range_end += range_size;
    }
}

/*
 * Returns the number of ranges.
 */
int queue_dispatch::get_num_ranges() 
{
    return num_ranges;
}

/*
 * Returns the next range in queue. 
 * out @ranges  The next range in queue.
 */
void queue_dispatch::get_range(range_desc& ranges)
{
    std::lock_guard<std::mutex> lock(q_mutex);
    if (range_queue.size() == 0) {
        ranges = {-1, 0, 0};
        return;
    }

    ranges = range_queue.front();
    range_queue.pop();
}
