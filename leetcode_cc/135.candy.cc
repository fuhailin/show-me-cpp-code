#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings)
    {
        int res = 0;
        int n = ratings.size();
        if (n == 0)
            return 0;
        vector<int> left(ratings.size(), 1);
        vector<int> right(ratings.size(), 1);

        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                right[i] = right[i + 1] + 1;
            }
        }

        for (int i = 0; i < n; i++) {
            res += max(left[i], right[i]);
        }
        return res;
    }
};