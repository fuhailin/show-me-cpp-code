#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        pair<int, int> biggest;
        int max_v = INT_MIN;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] > max_v){
                max_v = nums[i];
                biggest = {max_v, i};

            }
        }
        vector<int> left = {nums.begin(), nums.begin() + biggest.second};
        vector<int> right = {nums.begin()+ biggest.second + 1, nums.end()};
        TreeNode* root = new TreeNode(biggest.first);
        root->left = constructMaximumBinaryTree(left);
        root->right = constructMaximumBinaryTree(right);
        return root;
    }
};