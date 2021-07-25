#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    //创建并初始化set容器
    std::set<int> myset;
    // int a[5] = {1, 2, 3, 4, 5};
    //通过数组a的地址初始化，注意地址是从0到5（左闭右开区间）
    // std::vector<int> nums(a, a + 5);
    std::vector<int> nums{0, 1, 2, 3, 4, 5};

    myset.insert(nums.begin(), nums.end());
    cout << "myset size =" << myset.size() << endl;
    // for (auto x : myset) {
    //     std::cout << x << " ";
    // }
    return 0;
}