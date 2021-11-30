#include <iostream>
#include <thread>

#include "semaphore.h"
using namespace std;

sem_t sem(0);

void func1() {
    // do something
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "func1" << std::endl;
    sem.signal();
}

void func2() {
    sem.wait();
    //do something
    std::cout << "func2" << std::endl;
}

int main() {
    std::thread thread1(func1);
    std::thread thread2(func2);
    if (thread1.joinable())
        thread1.join();
    if (thread2.joinable())
        thread2.join();
}
