#include "bits/stdc++.h"

class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        deque<int> window;
        window.push_back(nums[0]);
        for (int i = 1; i < k; i++) {
            while (!window.empty() && nums[i] > window.back()) {
                window.pop_back();
            }
            window.push_back(nums[i]);
        }
        res.push_back(window.front());
        int left = 0;
        for (int right = k; right < n; right++) {
            if (nums[left++] == window.front()) {
                window.pop_front();
            }
            while (!window.empty() && nums[right] > window.back()) {
                window.pop_back();
            }
            window.push_back(nums[right]);
            res.push_back(window.front());
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {-7, -8, 7, 5, 7, 1, 6, 0};
    vector<int> res = so.maxSlidingWindow(test, 4);
    LOG(INFO) << res;
    return 0;
}
