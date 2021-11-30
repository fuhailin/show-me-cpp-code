#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        int max_value = nums[0], min_value = 0, sum = nums[0];
        vector<int> dpmax(n, 0), dpmin(n, 0);
        dpmax[0] = dpmin[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            dpmax[i] = max(dpmax[i - 1] + nums[i], nums[i]);
            max_value = max(max_value, dpmax[i]);

            dpmin[i] = min(dpmin[i - 1] + nums[i], nums[i]);
            min_value = min(min_value, dpmin[i]);
            sum += nums[i];
        }
        if ((sum - min_value) == 0) {
            return max_value;
        }
        return max(sum - min_value, max_value);
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<int> test = {-2, -3, -1};
    int res = s.maxSubarraySumCircular(test);
    cout << "res: " << res << endl;
    return 0;
}
