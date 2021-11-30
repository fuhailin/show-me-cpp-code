#include "bits/stdc++.h"

class Solution {
    // 均匀分布整数随机数生成器
    std::random_device rd;  //获取随机数种子
    std::mt19937 rng;
    vector<int> original;
    vector<int> nums;

   public:
    Solution(const vector<int>& nums) : rng(rd()) {
        this->nums = nums;
        this->original.resize(nums.size());
        copy(nums.begin(), nums.end(), original.begin());
    }

    vector<int> reset() {
        return original;
    }

    vector<int> shuffle() {
        for (int i = 0; i < nums.size(); ++i) {
            int j = i + rng() % (nums.size() - i);  // j : [ i, n - 1 ]
            swap(nums[i], nums[j]);
        }
        return nums;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 2, 3};
    Solution* obj = new Solution(nums);
    vector<int> param_1 = obj->reset();
    LOG(INFO) << "reset(): " << param_1;
    vector<int> param_2 = obj->shuffle();
    LOG(INFO) << "shuffle(): " << param_2;
    return 0;
}
