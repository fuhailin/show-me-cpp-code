// C program to demonstrate working of Semaphores
#include <glog/logging.h>
#include <semaphore.h>

#include <boost/thread.hpp>
#include <iostream>
#include <thread>

sem_t firstJobDone, secondJobDone;

void* func1(void* arg) {
    //wait
    LOG(INFO) << boost::this_thread::get_id() << " Entered..";

    //critical section
    sleep(1);

    //signal
    LOG(INFO) << boost::this_thread::get_id() << " Just Exiting...";
    sem_post(&firstJobDone);
}
void* func2(void* arg) {
    //wait
    sem_wait(&firstJobDone);
    LOG(INFO) << boost::this_thread::get_id() << " Entered..";

    //critical section
    sleep(1);

    //signal
    LOG(INFO) << boost::this_thread::get_id() << " Just Exiting...";
    sem_post(&secondJobDone);
}
void* func3(void* arg) {
    //wait
    sem_wait(&secondJobDone);
    LOG(INFO) << boost::this_thread::get_id() << " Entered..";

    //critical section
    sleep(1);

    //signal
    LOG(INFO) << boost::this_thread::get_id() << " Just Exiting...";
}

int main() {
    sem_init(&firstJobDone, 0, 0);
    sem_init(&secondJobDone, 0, 0);
    std::thread t1(func1, nullptr);
    sleep(2);
    std::thread t2(func2, nullptr);
    sleep(2);
    std::thread t3(func3, nullptr);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}