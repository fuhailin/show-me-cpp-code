#include "bits/stdc++.h"

class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size());
        stack<int> st;
        for (int i = temperatures.size() - 1; i >= 0; i--) {
            int num = temperatures[i];
            while (!st.empty() && num >= temperatures[st.top()]) {
                st.pop();
            }
            res[i] = st.empty() ? 0 : st.top() - i;
            st.push(i);
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test1 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> res = so.dailyTemperatures(test1);
    LOG(INFO) << "res: " << res;
    return 0;
}