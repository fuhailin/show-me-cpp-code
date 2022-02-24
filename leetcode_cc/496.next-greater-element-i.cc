#include "bits/stdc++.h"

class Solution {
   public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> hashmap;
        stack<int> st;
        for (int i = nums2.size() - 1; i >= 0; i--) {
            int num = nums2[i];
            while (!st.empty() && num > st.top()) {
                st.pop();
            }
            hashmap[num] = st.empty() ? -1 : st.top();
            st.push(num);
        }
        vector<int> res(nums1.size());
        for (int i = 0; i < nums1.size(); ++i) {
            res[i] = hashmap[nums1[i]];
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test1 = {4, 1, 2};
    vector<int> test2 = {1, 3, 4, 2};
    vector<int> res = so.nextGreaterElement(test1, test2);
    LOG(INFO) << "res: " << res;
    return 0;
}
