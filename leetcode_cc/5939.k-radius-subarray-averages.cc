#include "bits/stdc++.h"

class Solution {
   public:
    vector<int> getAverages(vector<int>& nums, int k) {
        if(k == 0) return nums;
        int n = nums.size();
        vector<int> res(n, -1);
        if (k >= n) return res;
        int left, right;
        long long sum = 0;
        for (int i = 0; i <= k; i++) {
            sum += nums[i];
        }
        for (int mid = 1; mid < n; mid++) {
            left = mid - k;
            right = mid + k;
            if (right >= n) {
                return res;
            } else if (left >= 0) {
                if(left == 0) {
                    sum += nums[right];
                    res[mid] = sum / (2 * k + 1);
                } else {
                    sum += nums[right];
                    sum -= nums[left - 1];
                    res[mid] = sum / (2 * k + 1);
                }
            } else {
                sum += nums[right];
            }
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1000};
    vector<int> res = so.getAverages(test, 0);
    LOG(INFO) << res;
    return 0;
}
