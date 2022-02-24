#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    TreeNode* dfs(vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = (left + right) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = dfs(nums, left, mid - 1);
        root->right = dfs(nums, mid + 1, right);
        return root;
    }

   public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = dfs(nums, 0, nums.size() - 1);
        return root;
    }
};