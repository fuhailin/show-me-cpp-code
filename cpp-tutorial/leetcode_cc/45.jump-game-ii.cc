#include <iostrem>
#include <vector>
using namespace std;

class Solution {
   public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = 0;
        dp[1] = 

    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<int> test = {2,3,1,1,4};
    int res = s.jump(test);
    cout << "res: " << res << endl;
    return 0;
}
