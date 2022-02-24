#include "bits/stdc++.h"


class RangeFreqQuery {
    unordered_map<int, vector<int>> memo;
public:
    RangeFreqQuery(vector<int>& arr) {
        for(int i = 0 ; i < arr.size(); i++) {
            memo[arr[i]].push_back(i);
        }
    }

    int query(int left, int right, int value) {
        if (!memo.count(value))
            return 0;
        
        auto &v = memo[value];
        auto r = upper_bound(v.begin(), v.end(), right); // 大于目标元素的第一个数/位置
        auto l = lower_bound(v.begin(), v.end(), left); // 大于等于 目标元素 的数值和下标
        return r - l;
    }
};


int main(int argc, char const* argv[]) {
    vector<int> arr = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    RangeFreqQuery* obj = new RangeFreqQuery(arr);
    int param_1 = obj->query(1,2,4);
    cout << param_1 << endl;
    return 0;
}
/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 *
 */