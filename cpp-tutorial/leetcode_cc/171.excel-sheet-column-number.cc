#include <gtest/gtest.h>

#include <cmath>
#include <string>
using namespace std;

class Solution {
   public:
    int titleToNumber(string columnTitle) {
        int res = 0;
        for (size_t i = 0; i < columnTitle.size(); ++i) {
            int carry = columnTitle[i] - 'A' + 1;
            res = res * 26 + carry;
        }
        return res;
    }
};

TEST(LeetCode, Excel表列序号) {
    Solution s;
    {
        std::vector<string> input = {"A", "AB", "ZY"};
        std::vector<int> result = {1, 28, 701};
        for (int i = 0; i < input.size(); ++i) {
            int ret = s.titleToNumber(input[i]);
            EXPECT_EQ(ret, result[i]);
        }
    }
}