#include <glog/logging.h>
#include <glog/stl_logging.h>

#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
    // 均匀分布整数随机数生成器
    std::random_device rd;  //获取随机数种子
    std::mt19937 rng;
    unordered_map<int, int> dict;
    int remain;
    int rows, cols;

   public:
    Solution(int m, int n) : rng(rd()) {
        rows = m, cols = n;
        remain = rows * cols;
    }

    vector<int> flip() {
        int idx = rng() % remain--;  // tmp : [0, remain - 1]
        vector<int> res;
        if (dict.count(idx)) {
            res = {dict[idx] / cols, dict[idx] % cols};
        } else {
            res = {idx / cols, idx % cols};
        }
        // swap
        if (dict.count(remain)) {
            dict[idx] = dict[remain];
        } else {
            dict[idx] = remain;
        }
        return res;
    }

    void reset() {
        remain = rows * cols;
        dict.clear();
    }
};
int main(int argc, char const* argv[]) {
    Solution* obj = new Solution(3, 1);
    vector<int> param_1 = obj->flip();
    LOG(INFO) << param_1;
    vector<int> param_2 = obj->flip();
    LOG(INFO) << param_2;
    vector<int> param_3 = obj->flip();
    LOG(INFO) << param_3;
    obj->reset();
    param_1 = obj->flip();
    LOG(INFO) << param_1;
    param_2 = obj->flip();
    LOG(INFO) << param_2;
    param_3 = obj->flip();
    LOG(INFO) << param_3;
    return 0;
}