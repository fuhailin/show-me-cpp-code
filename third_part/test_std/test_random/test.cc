#include <iostream>
#include <random>

using namespace std;

int main() {
    // 均匀分布整数随机数生成器
    std::mt19937 rng(std::random_device{}());
    for (int i = 0; i < 10; i++) {
        uint tmp = rng();
        cout << tmp << endl;
    }

    // 正态分布的随机数,均值和标准差，这里分别输入5, 2
    // std::mt19937 rng(std::random_device{}());
    std::normal_distribution<double> nd(5, 2);
    for (int i = 0; i < 5; i++) {
        cout << nd(rng) << endl;
    }

    std::random_device rd;   //获取随机数种子
    std::mt19937 gen(rd());  //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 9);

    for (int n = 0; n < 5; ++n)
        std::cout << dis(gen) << std::endl;

    // 随机数种子
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 rand_num(seed);	 // 大随机数
	cout << "随机数种子:\n" << rand_num() << endl;


    return 0;
}