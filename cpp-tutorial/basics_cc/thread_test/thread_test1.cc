// example.cpp
// g++ -std=c++14 example.cpp -lpthread -o example
#include <iostream>
#include <thread>

void thread_sleep(int sleep_seconds, bool verbose) {
    std::thread::id this_id = std::this_thread::get_id();
    if (verbose) {
        std::cout << "Thread " << this_id << " sleeping for " << sleep_seconds << " seconds ..." << std::endl;
    }
    std::chrono::seconds sleep_duration{sleep_seconds};
    std::this_thread::sleep_for(sleep_duration);
    if (verbose) {
        std::cout << "Thread " << this_id << " sleeping complete! " << std::endl;
    }
}

int main() {
    std::thread new_thread{thread_sleep, 5, true};
    thread_sleep(1, true);
    new_thread.join();
    // new_thread.detach();
    return 0;
    // new_thread destructor will be called
}