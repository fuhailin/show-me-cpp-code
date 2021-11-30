#include "bits/stdc++.h"

class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int res = INT_MIN;
        for(int i = 0; i < colors.size(); i++) {
            for(int j = i; j < colors.size(); j++) {
                if(colors[j] != colors[i]) {
                    res = max(res, abs(j - i));
                }
            }
        }
        return res == INT_MIN ? 0 : res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {0,0,0};
    int res = so.maxDistance(test);
    cout << "res: " << res << endl;
    return 0;
}
