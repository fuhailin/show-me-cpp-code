#include <gtest/gtest.h>

#include <iostream>
#include <vector>
using namespace std;

/*
斐波那契数，通常用 F(n) 表示，形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1
给你 n ，请计算 F(n) 。
*/
class Solution {
   public:
    int fib(int n) {
        if (n < 2) return n;
        int dp0 = 0;
        int dp1 = 1;
        int dpn;
        for (int i = 2; i <= n; ++i) {
            dpn = dp1 + dp0;
            dp0 = dp1;
            dp1 = dpn;
        }
        return dpn;
    }
};

TEST(LeetCode, fibonacci_number) {
    Solution s;
    {
        std::vector<int> input = {2, 3, 4};
        std::vector<int> result = {1, 2, 3};
        for (int i = 0; i < input.size(); ++i) {
            int ret = s.fib(input[i]);
            EXPECT_EQ(ret, result[i]);
        }
    }
}