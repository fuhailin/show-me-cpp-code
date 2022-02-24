#include "bits/stdc++.h"

class RangeFreqQuery {
    unordered_map<int, vector<int>> memo;

    // 小于等于
    int mylower(vector<int>& vec, int value) {
        int left = -1, right = vec.size(), mid;
        while (left + 1 != right) {
            mid = (left + right) / 2;
            if (value > vec[left]) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return vec[left] == value ? left : -1;
    }

    // 大于等于
    int myupper(vector<int>& vec, int value) {
        int left = -1, right = vec.size(), mid;
        while (left + 1 != right) {
            mid = (left + right) / 2;
            if (value < vec[left]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return vec[right] == right ? right : vec.size();
    }

   public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            if (memo.count(arr[i])) {
                memo[arr[i]].push_back(i);
            } else {
                memo[arr[i]] = vector<int>{i};
            }
        }
    }

    int query(int left, int right, int value) {
        int res = 0;
        if (!memo.count(value)) return res;
        LOG(INFO) << memo[value];
        int left_i = myupper(memo[value], value);
        int right_i = mylower(memo[value], value);
        LOG(INFO) << left_i << ", " << right_i;
        return right_i - left_i + 1;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> arr = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    RangeFreqQuery* obj = new RangeFreqQuery(arr);
    int param_1 = obj->query(4, 10, 12);
    cout << param_1 << endl;
    return 0;
}
/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 *
 */