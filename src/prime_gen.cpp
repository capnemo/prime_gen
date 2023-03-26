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
#include <limits>

#include "primes.h"
#include "queue_dispatch.h"
#include "file_writer.h"

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

    bool isMax = false;
    unsigned int exp;
    if (std::string(argv[1]) == std::string("max")) {
        isMax = true;
        exp = 19;
    } else 
        exp = std::strtoull(argv[1], nullptr, 10);

    //Handke the case of max!
    if ((exp < 1) || (exp > 19)) {
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

    int p_exp = exp;
    if (exp > 7)  {
        p_exp = exp/2.0 + 0.5;
        if (isMax == true)
            p_exp = std::numeric_limits<uint32_t>::max();
    }

    ulong max_prime = powl(10, p_exp);
    ulong_vec prime_seeds;
    std::cout << "Generating first primes" << std::endl;
    primes::generate_first_primes(max_prime, prime_seeds);
    std::cout << "Done with first primes" << std::endl;

    //Removing 2 and 3 from prime_seeds causes errors. TBI
    if (output_file != "")
        file_writer::write_file(prime_seeds, output_file);

    if (exp == p_exp) {
        std::cout << "total number of primes is " << prime_seeds.size() <<
        std::endl;
        return 0;
    }

    ulong prime_factor_limit = max_prime;
    max_prime = (isMax == true) ? std::numeric_limits<uint64_t>::max()
                                  :powl(10, exp);

    queue_dispatch range_q(prime_factor_limit, max_prime);
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
