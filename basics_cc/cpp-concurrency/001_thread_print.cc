#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void do_some_work(int num) {
    std::cout << "thread: " << num << std::endl;
}

int main(int argc, char const *argv[]) {
    int threadNums = 3;
    std::vector<std::thread> threadList;
    threadList.reserve(threadNums);

    // 1 创建 threadNums 个线程
    for (int idx = 0; idx < threadNums; ++idx) {
        threadList.emplace_back(std::thread{do_some_work, idx});
    }

    std::cout << "work in main thread" << std::endl;

    // 2 终止 threadNums 个线程
    for (int idx = 0; idx < threadNums; ++idx) {
        threadList[idx].join();
    }

    std::cout << "main thread end" << std::endl;
    return 0;
}