/*
https://kezunlin.me/post/f241bd30/
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <chrono>    //std::chrono::seconds
#include <future>    //std::future std::promise
#include <iostream>  //std::cout std::endl
#include <thread>    //std::thread
#include <utility>   //std::ref

class ThreadPool {
   public:
    explicit ThreadPool(size_t size) : work_(io_service_) {
        for (size_t i = 0; i < size; ++i) {
            workers_.create_thread(
                boost::bind(&boost::asio::io_service::run, &io_service_));
        }
    }

    ~ThreadPool() {
        std::cout << "~ThreadPool" << std::endl;
        io_service_.stop();  // stop before join_all
        workers_.join_all();
    }

    // Add new work item to the pool.
    template <class F>
    void Enqueue(F f) {
        io_service_.post(f);
        //sync, return immediately
    }

   private:
    boost::thread_group workers_;
    boost::asio::io_service io_service_;
    boost::asio::io_service::work work_;
};

boost::mutex io_mutex;

void count(int id) {
    for (int i = 0; i < 10; i++) {
        boost::mutex::scoped_lock lock(io_mutex);
        std::cout << id << ":" << i << std::endl;
    }
}

void test_thread() {
    boost::thread thrd1(boost::bind(&count, 1));
    boost::thread thrd2(boost::bind(&count, 2));
    thrd1.join();
    thrd2.join();
}

void print(int i) {
    boost::mutex::scoped_lock lock(io_mutex);
    std::cout << "print() #" << boost::this_thread::get_id() << std::endl;
    std::cout << "hello " << i << std::endl;
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    std::cout << "world " << i << std::endl;
}

void test_thread_pool() {
    // Create a thread pool of 4 worker threads.
    ThreadPool pool(4);

    // Queue a bunch of work items.
    for (int i = 0; i < 8; ++i) {
        pool.Enqueue(boost::bind(&print, i));
    }
}

void do_task(std::promise<int>& promiseObj) {
    boost::mutex::scoped_lock lock(io_mutex);
    std::cout << "Inside thread: " << std::this_thread::get_id() << std::endl;
    std::cout << "Inside thread: sleep 2 seconds... " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    promiseObj.set_value(35);
}

void test_future() {
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::cout << "create thread..." << std::endl;
    std::thread th(do_task, std::ref(promiseObj));

    std::cout << "futureObj.get() block main thread." << std::endl;
    std::cout << futureObj.get() << std::endl;

    th.join();
    std::cout << "after join" << std::endl;
}

/*
std::bind
bind预先绑定的参数需要传具体的变量或值进去，对于预先绑定的参数，是pass-by-value的；[使用std::ref()可以pass by reference]
对于不事先绑定的参数，需要传std::placeholders进去，从_1开始，依次递增。placeholder是pass-by-reference的；
*/

int main(int argc, char* argv[]) {
    //test_thread();
    //test_thread_pool();
    test_future();
    return 0;
}
