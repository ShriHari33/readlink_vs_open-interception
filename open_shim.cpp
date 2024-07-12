#include <iostream>
#include <dlfcn.h>
#include <sys/types.h>
#include <stdio.h>
#include <mutex>
#include <fstream>
#include <chrono>

FILE* open_file_nanoseconds{};

extern "C" int open(const char* path, int flags)
{
    using std::chrono::nanoseconds, std::chrono::high_resolution_clock;


    auto start = high_resolution_clock::now();

    auto real_open =
        reinterpret_cast<int (*)(const char*, int)>(dlsym(RTLD_NEXT, "open"));


    if (real_open == nullptr)
    {
        fprintf(stderr, "Open failed\n");
        exit(-1);
    }

    auto end = high_resolution_clock::now();


    auto ret = real_open(path, flags);


    auto duration_ns = std::chrono::duration_cast<nanoseconds>(end - start);

    fprintf(open_file_nanoseconds, "%ld\n", duration_ns.count());

    return ret;
}

void __attribute__((constructor)) cons()
{
    // fprintf(stdout, "In CTOR\n");
    open_file_nanoseconds = fopen("open_nanoseconds.txt", "w");

    if (open_file_nanoseconds == nullptr)
    {
        fprintf(stderr, "In CTOR: Failed to open the open_nanoseconds file. EXITING\n");
        exit(-1);
    }
}


void __attribute__((destructor)) des()
{
    // fprintf(stdout, "In DTOR\n");
    fclose(open_file_nanoseconds);
}