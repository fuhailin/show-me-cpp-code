#include <omp.h>
#include <sys/param.h>
#include <unistd.h>

#include <iostream>

#define THREAD_NUM 5

int main() {
    omp_set_num_threads(THREAD_NUM);  // set number of threads in "parallel" blocks
#pragma omp parallel
    {
        std::cout << "Hello World" << std::endl;
    }
    return 0;
}