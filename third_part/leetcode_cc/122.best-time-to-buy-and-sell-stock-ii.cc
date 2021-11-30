#include <vector>
using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int tmp;
        for (size_t i = 1; i < prices.size(); i++) {
            tmp = prices[i] - prices[i - 1];
            if (tmp > 0) {
                res += tmp;
            }
        }
        return res;
    }
};