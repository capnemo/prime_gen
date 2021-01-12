#include <thread>
#include <fstream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "prime_types.h"

/*
 * Class to write input buffers to a file in order. 
 * Runs its own write thread.
 */
#ifndef FILE_WRITER_H
#define FILE_WRITER_H
enum {
    empty = 0,
    full,
    flushed
};

struct buffer {
    int status;
    ulong_vec* buffer;
};

class file_writer {
    public:
    file_writer() {};
    file_writer(std::string file_name, int num_buffers):
             out_stream(file_name, std::ofstream::out | std::ofstream::app), 
             write_thread(&file_writer::flush_buffers, this),
             buffer_status(num_buffers, {empty, nullptr}) {}

    file_writer(int num_buffers):
            buffer_status(num_buffers, {empty, nullptr}), 
            file_exists(false) {}

    static void write_file(ulong_vec numbers, std::string file_name);
    bool init();
    void add_buffer(int id, ulong_vec* buf);
    void stop_thread();
    ulong get_num_primes();

    private:
    void flush_buffers();
    void write_to_file(ulong_vec* numbers);
    void print_progress(int blocks_written, int total);

    std::ofstream out_stream;
    std::vector<struct buffer> buffer_status;
    std::mutex buffer_mtx;
    std::mutex cv_mtx;
    std::condition_variable buffer_cv;
    std::thread write_thread;
    int last_written = -1;
    ulong total_primes = 0;
    bool file_exists = true;
    std::atomic<bool> incoming{true};
};
static file_writer dummy_file_writer;
#endif /* FILE_WRITER_H */
