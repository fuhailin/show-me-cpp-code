#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        int cand1 = -1, cand2 = -1;
        int votes1 = 0, votes2 = 0;
        for (int& num : nums) {
            if (num == cand1) {
                votes1++;
            } else if (num == cand2) {
                votes2++;
            } else if (votes1 == 0) {
                cand1 = num;
                votes1 = 1;
            } else if (votes2 == 0) {
                cand2 = num;
                votes2 = 1;
            } else {
                votes1--;
                votes2--;
            }
        }

        // 第2阶段 - 计数, 数目要超过三分之一
        votes1 = 0, votes2 = 0;
        for (auto& num : nums) {
            if (num == cand1)
                votes1++;
            else if (num == cand2)
                votes2++;
        }

        if (votes1 > n / 3) res.push_back(cand1);
        if (votes2 > n / 3) res.push_back(cand2);
        return res;
    }
};