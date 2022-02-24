#include <chrono>  //时间
#include <iostream>
#include <thread>

using namespace std;

void hello() {
    cout << "Hello World from new thread." << endl;
}

int main() {
    thread t(hello);
    t.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  //睡眠1000毫秒
    return 0;
}
