#include <iostream>
#include <algorithm>

#include "file_writer.h"

/*
 * Checks if the file is open.
 */
bool file_writer::init()
{
    if (out_stream.is_open() == false) 
        return false;

    return true;
}

/*
 *  Adds a buffer to the write queue. 
 *  in @id              buffer id.
 *  in @input_buffer    buffer to be written.
 */
void file_writer::add_buffer(int id, ulong_vec* input_buffer)
{
    std::unique_lock<std::mutex> lck(buffer_mtx);

    buffer_status[id].status = full;
    buffer_status[id].buffer = input_buffer;
    
    buffer_cv.notify_one();
}

/*
 * Writes buffers to the file in order. Runs in its own thread.
 */
void file_writer::flush_buffers()
{
    while (incoming == true) {
        std::unique_lock<std::mutex> lck(buffer_mtx);
        buffer_cv.wait(lck);

        if (last_written >= 0)
            print_progress(last_written, buffer_status.size());

        int i = last_written + 1;
        while (buffer_status[i].status == full) {
            write_to_file(buffer_status[i].buffer);
            buffer_status[i].status = flushed;
            last_written = i;
            i++;
        }
        if (last_written == buffer_status.size() - 1)
            break;
    }
}

/*
 *  Writes the buffers to the output file. Deletes the buffer after the write
 *  in @numbers Buffers to be written.
 */
void file_writer::write_to_file(ulong_vec* numbers)
{
    total_primes += numbers->size();
    std::string str_buf = "";
    for (auto num:*numbers)  
        str_buf += std::to_string(num) + '\n';

    out_stream << str_buf;
    delete numbers;
}
/*
 *  Stops the write thread and calls join on it. Flushes all the remaining
 *  buffers. 
 */
void file_writer::stop_thread()
{
    incoming = false;
    std::unique_lock<std::mutex> lck(buffer_mtx);
    buffer_cv.notify_one();
    lck.unlock();
    
    write_thread.join();

    for (auto m:buffer_status) 
        if (m.status == full)  
            write_to_file(m.buffer);

    out_stream.flush();
    print_progress(buffer_status.size(), buffer_status.size());
    std::cerr << std::endl;
}

/*
 * static function to write a single buffer to the output file. Closes
 * the file at return.
 * in @numbers   buffer to be written.
 * in @file_name output file.
 */
void file_writer::write_file(ulong_vec numbers, std::string file_name)
{
    std::ofstream stream = std::ofstream(file_name);
    std::ofstream* ostr = &stream;

    if (ostr->is_open() == false)  {
        std::cerr << "Cannot open file for writing" << std::endl;
        return;
    }
 
    std::for_each(numbers.begin(), numbers.end(), [ostr](ulong p)
                  { *ostr << p << std::endl;});
}

/*
 * Prints progress thus far.
 * @blocks_written  Blocks written thus far.
 * @total           Total number of blocks to be written.
 */
void file_writer::print_progress(int blocks_written, int total)
{
    std::string t_str = std::to_string(total);
    std::string b_str = std::to_string(blocks_written);
    std::string print_str = std::string('0', t_str.size() - b_str.size())
                             + b_str + "/" + t_str;

    int len = 2 * t_str.size() + 1;
    for (int i = 0; i < len; i++) 
        std::cerr << "\b";
    std::cerr << print_str << std::flush;
}
