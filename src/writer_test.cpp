#include <iostream>
#include "file_writer.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
    file_writer fw("xx", 10);
    if (fw.init() == false) {
        std::cout << "error -- cannot open file" << std::endl;
        return -1;
    }

    std::vector<int> v({0,9,2,3,4,5,6,7,8,1});
    for (auto m:v) {
        ulong_vec* x = new ulong_vec({ulong(m)});
        sleep(1);
        fw.add_buffer(x,m);
    }

    std::cout << "stopping the thread" << std::endl;
    fw.stop_thread();
}
