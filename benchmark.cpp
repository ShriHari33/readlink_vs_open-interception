#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sys/types.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <mutex>
#include <fstream>

/*
    global to keep track of the PID and FD of the device opened by the program.  
    This is necessary for 'readlink'
*/
pid_t pid{};
int fd{};
std::ofstream readlink_file_nanoseconds{};

/*
    The size of the buffer used to store the path of the device opened by the program.  
    This is necessary for 'readlink'
*/
constexpr size_t BUF_SIZE{ 2048 };

void readlink_benchmark()
{
    using std::chrono::nanoseconds, std::chrono::high_resolution_clock;
    
    auto start = high_resolution_clock::now();

    char path[BUF_SIZE];
    char buf[BUF_SIZE];

    sprintf(path, "/proc/%d/fd/%d", pid, fd);
    auto ret = readlink(path, buf, BUF_SIZE - 1);

    if (ret == -1)
    {
        fprintf(stderr, "Readlink Failed\n");
        exit(-1);
    }

    // manually insert null terminator as readlink does not do this
    buf[ret] = '\0';

    auto end = high_resolution_clock::now();


    auto duration_ns = std::chrono::duration_cast<nanoseconds>(end - start);
    readlink_file_nanoseconds << duration_ns.count() << std::endl;
}

int main()
{
    readlink_file_nanoseconds.open("readlink_nanoseconds.txt");
    pid = getpid();

    for (size_t i = 0; i < 1000; ++i)
    {
        fd = open("/dev/video0", O_RDWR); // open benchmark
        
        readlink_benchmark(); // readlink benchmark

        close(fd);
    }

    readlink_file_nanoseconds.close();

    std::cout << "Benchmark complete.\nGenerated \"readlink_nanoseconds.txt\" & \"open_nanoseconds.txt\"\n";
}