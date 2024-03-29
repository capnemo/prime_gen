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
#include <climits>

#include "primes.h"
#include "queue_dispatch.h"
#include "file_writer.h"

using pair_64 = std::pair<uint64_t, uint64_t>;

void handle_limit_arg(const char* limit, pair_64& prange);
void usage(const char* prog_name)
{
    std::cout << prog_name << " <exponent> " << "[-f <output file name>]" 
    << std::endl;
    std::cout << "exponent should be between 1 and 19 or max" <<std::endl;
}

int main(int argc, char *argv[])
{
    if ((argc != 2)  && (argc != 4)) {
        usage(argv[0]);
        return -1;
    }

    std::string output_file = "";
    if (argc == 4) {
        if (std::string(argv[2]) == std::string("-f")) {
            output_file = argv[3];
        } else {
            usage(argv[0]);
            return -1;
        }
    }

    pair_64 range_limits;
    handle_limit_arg(argv[1], range_limits);
    if ((range_limits.first == 0) && (range_limits.second == 0)) {
        usage(argv[0]);
        return -1;
    }
        
    ulong_vec prime_seeds;
    std::cout << "Generating first primes" << std::endl;
    primes::generate_first_primes(range_limits.first, prime_seeds);
    std::cout << "Done with first primes" << std::endl;

    if (output_file != "")
        file_writer::write_file(prime_seeds, output_file);

    if (range_limits.second == 0) {
        std::cout << "total number of primes is " << prime_seeds.size() <<
        std::endl;
        return 0;
    }

    queue_dispatch range_q(range_limits.first, range_limits.second);
    range_q.fill_queue();
    file_writer *fw = nullptr;
    if (output_file != "") {
        fw = new file_writer(output_file, range_q.get_num_ranges());
        if (fw->init() == false) {
            std::cerr << "Cannot open file" << std::endl;
            return -1;
        }
    }

    std::vector<primes*> prime_ranges;
    std::vector<std::thread> thread_list;
    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        primes *pm = new primes(i, range_q, prime_seeds, fw);
        prime_ranges.push_back(pm);
        thread_list.push_back(std::thread(&primes::fetch_ranges, pm));
    }

    for (int i = 0; i < thread_list.size(); i++) 
        thread_list[i].join();

    if (fw != nullptr) {
        fw->stop_thread();
        delete fw;
    }

    ulong total = prime_seeds.size();
    for (auto p:prime_ranges) {
        total += p->get_prime_count();
        delete p;
    }
        
    std::cout << "total number of primes is " << total << std::endl;
}

void handle_limit_arg(const char* limit, pair_64& prange)
{
    prange.first = 0;
    prange.second = 0;
    if (std::string(limit) == std::string("max")) {
        prange.first = powl(10, 10);
        prange.second = std::numeric_limits<uint64_t>::max();
        return;
    } 

    uint64_t exp = strtoul(limit, nullptr, 10);
    if (exp != ULLONG_MAX) {
        if (exp <= 8) {
            prange.first = powl(10, exp);
            return;
        }

        if (exp <= 19) {
            prange.first = powl(10, exp/2 + 0.5);
            prange.second = powl(10, exp);
        }
    }

    return;
}
