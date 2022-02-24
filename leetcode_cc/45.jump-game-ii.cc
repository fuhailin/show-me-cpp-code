#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int jump(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        int curDistance = 0, nexDistance = 0;
        for (int i = 0; i < n - 1; ++i) {
            nexDistance = max(nexDistance, i + nums[i]);
            if (i == curDistance) {
                curDistance = nexDistance;
                res++;
            }
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<int> test = {2, 1, 1, 1, 4};
    int res = s.jump(test);
    cout << "res: " << res << endl;
    return 0;
}
