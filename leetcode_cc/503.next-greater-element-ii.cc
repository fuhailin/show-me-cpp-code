#include "bits/stdc++.h"
class Solution {
   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        stack<int> st;
        for (int i = 2 * n - 1; i >= 0; i--) {
            int num = nums[i % n];
            while (!st.empty() && num >= st.top()) {
                st.pop();
            }
            res[i % n] = st.empty() ? -1 : st.top();
            st.push(num);
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test1 = {1, 2, 3};
    vector<int> res = so.nextGreaterElements(test1);
    LOG(INFO) << "res: " << res;
    return 0;
}
