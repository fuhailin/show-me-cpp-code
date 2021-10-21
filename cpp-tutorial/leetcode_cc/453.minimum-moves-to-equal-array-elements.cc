#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int minMoves(vector<int>& nums) {
        int res = 0;
        int minNum = *min_element(nums.begin(), nums.end());
        for (int num : nums) {
            res += num - minNum;
        }
        return res;
    }
};

int main(int argc, const char** argv) {
    Solution so;
    vector<int> test = {1, 2, 3};
    int res = so.minMoves(test);
    cout << "res: " << res << endl;
    return 0;
}