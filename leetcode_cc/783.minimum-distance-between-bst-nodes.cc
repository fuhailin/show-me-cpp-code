#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    void dfs(TreeNode* root, int& pre, int& minDiff) {
        if (!root) {
            return;
        }
        dfs(root->left, pre, minDiff);
        if (pre == -1) {
            pre = root->val;
        } else {
            minDiff = min(root->val - pre, minDiff);
            pre = root->val;
        }
        dfs(root->right, pre, minDiff);
    }

   public:
    int minDiffInBST(TreeNode* root) {
        int minDiff = INT_MAX, pre = -1;
        dfs(root, pre, minDiff);
        return minDiff;
    }
};