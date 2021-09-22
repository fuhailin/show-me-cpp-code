#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
   public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int weight = sum / 2;
        vector<int> dp(weight + 1, 0);

        for (int j = weight; j >= stones[0]; j--) {
            dp[j] = stones[0];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = weight; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - 2 * dp[weight];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {31, 26, 33, 21, 40};
    int res = so.lastStoneWeightII(test);
    cout << "res: " << res << endl;
    return 0;
}
