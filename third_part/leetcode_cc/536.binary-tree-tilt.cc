#include "include/TreeNode.h"

class Solution {
    int ans = 0;
    int dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left = dfs(root->left);
        int right = dfs(root->right);
        ans += abs(left - right);
        int res = root->val + left + right;
        return res;
    }

   public:
    int findTilt(TreeNode* root) {
        dfs(root);
        return ans;
    }
};