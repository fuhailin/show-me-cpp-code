#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int res = nums[0];
        vector<int> dp_max(n, 0);
        vector<int> dp_min(n, 0);
        dp_max[0] = nums[0];
        for (int i = 1; i < n; i++) {
            dp_max[i] = max(max(dp_max[i - 1] * nums[i], dp_min[i - 1] * nums[i]), nums[i]);
            dp_min[i] = min(min(dp_min[i - 1] * nums[i], dp_max[i - 1] * nums[i]), nums[i]);
            res = max(res, max(dp_max[i], dp_min[i]));
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<int> test = { -2};
    int res = s.maxProduct(test);
    cout << "res: " << res << endl;
    return 0;
}
