#include <vector>
using namespace std;

class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        sort(beans.begin(), beans.end());

        

        vector<long long> preSum(beans.size());
        preSum[0] = beans[0];
        for(int i = 1; i < beans.size(); i++) {
            preSum[i] = preSum[i - 1] + beans[i];
        }
        long long res = (preSum);
        for(int i = 1; i < beans.size(); i++) {
            res = min(res, preSum[])
        }


    }
};