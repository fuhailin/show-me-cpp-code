#include <iostream>
#include <vector>

class Solution {
   public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size() - 1;
        int carry = 1;
        while (carry && n >= 0) {
            int tmp = digits[n] + carry;
            digits[n] = (tmp) % 10;
            carry = tmp / 10;
            n--;
        }
        if (carry != 0) {
            std::reverse(digits.begin(), digits.end());
            digits.push_back(carry);
            std::reverse(digits.begin(), digits.end());
        }
        return digits;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {4, 3, 2, 1};

    return 0;
}
