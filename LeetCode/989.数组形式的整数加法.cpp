#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        vector<int> res;
        int n = A.size();
        int i = n - 1, carry = 0, sum = 0;
        int x, y;
        while (i >= 0 || K != 0) {
            x = i >= 0 ? A[i] : 0;
            y = K != 0 ? K % 10 : 0;
            sum = x + y + carry;
            carry = sum / 10;
            res.push_back(sum % 10);
            --i;
            K = K / 10;
        }
        if (carry != 0) {
            res.push_back(carry);
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};

void print(std::vector<int> const& input) {
    for (auto const& i : input) {
        std::cout << i << " ";
    }
}

int main() {
    vector<int> tmp{2, 7, 4};
    Solution solu;
    vector<int> test = solu.addToArrayForm(tmp, 181);
    print(test);
    return 0;
}
