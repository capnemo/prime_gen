#include <vector>
#include <set>
#include <map>

#ifndef PRIME_TYPES_H
#define PRIME_TYPES_H

using ulong_pair = std::pair<ulong, ulong>;
using ulong_vec = std::vector<ulong>;
using ulong_set = std::set<ulong>;

struct range_desc {
    int serial;
    ulong rbegin;
    ulong rend;
};

struct write_buffer {
    int id;
    ulong_vec *buffer;
};

#endif /* PRIME_TYPES_H */
