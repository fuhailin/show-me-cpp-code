#include "bits/stdc++.h"

class Solution {
   public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty()) return 0;
        int res = 0, healthTime = -1;
        for (int time : timeSeries) {
            res += duration;  //只要受到攻击则追加伤害时长
            if (time < healthTime) {
                // 如果当前攻击时上次攻击造成的伤害还未消除，只需要减去两次伤害的叠加时长即可
                res -= healthTime - time;
            }
            healthTime = time + duration;  //记录恢复健康的时刻
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2};
    int res = so.findPoisonedDuration(test, 2);
    cout << "res: " << res << endl;
    return 0;
}
