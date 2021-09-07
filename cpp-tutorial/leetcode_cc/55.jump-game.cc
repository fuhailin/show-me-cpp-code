#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    bool canJump(vector<int>& nums) {
        int n = nums.size(), reach = 0;
        for (int i = 0; i < n; ++i) {
            if (i > reach) {
                return false;
            }
            reach = max(i + nums[i], reach);
        }
        return true;
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<int> test = {2, 3, 1, 1, 4};
    bool res = s.canJump(test);
    cout << "res: " << res << endl;
    return 0;
}
