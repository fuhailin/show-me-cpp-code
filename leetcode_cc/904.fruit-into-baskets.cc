#include "bits/stdc++.h"

class Solution {
    unordered_map<int, int> basket;

   public:
    int totalFruit(vector<int>& fruits) {
        int left = 0, res = INT_MIN, volume = 0;
        for (int right = 0; right < fruits.size(); right++) {
            int fruit = fruits[right];
            basket[fruit]++;
            volume++;
            if (basket.size() <= 2) {
                res = max(volume, res);
            } else {
                while (basket.size() > 2) {
                    int x = fruits[left];
                    basket[x]--;
                    if (basket[x] == 0) {
                        basket.erase(x);
                    }
                    volume--;
                    left++;
                }
            }
        }
        return res == INT_MIN ? 0 : res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    int res = so.totalFruit(test);
    cout << "res: " << res << endl;
    return 0;
}
