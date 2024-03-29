#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
   public:
   /*
   动态规划
   */
    int trap0(vector<int>& height) {
        int res = 0;
        int n = height.size();
        vector<int> left(n, 0), right(n, 0);
        int tmp_max = INT_MIN;
        for (int i = 0; i < n; i++) {
            tmp_max = max(height[i], tmp_max);
            left[i] = tmp_max;
        }
        tmp_max = INT_MIN;
        for (int i = height.size() - 1; i >= 0; --i) {
            tmp_max = max(height[i], tmp_max);
            right[i] = tmp_max;
        }
        for (int i = 1; i < n; i++) {
            res += min(right[i], left[i]) - height[i];
        }
        return res;
    }

    int trap(vector<int>& height) {
        int res = 0;
        int n = height.size();
        vector<int> visited(n);
        priority_queue<int> heap;
        heap.push(height[0]);
        heap.push(height[n - 1]);
        while (!heap.empty())
        {
            int element = heap.top();
            
        }
        

    }
};

int main(int argc, const char** argv) {
    Solution so;
    vector<int> test = {4, 2, 0, 3, 2, 5};
    int res = so.trap(test);
    cout << "res: " << res << endl;
    return 0;
}