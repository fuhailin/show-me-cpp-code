#include <utility>

#include "include/TreeNode.h"
using namespace std;

class Solution {
    pair<int, int> dfs(TreeNode* root) {
        if (!root) {
            return {0, 0};
        }
        pair<int, int> left = dfs(root->left);
        pair<int, int> right = dfs(root->right);
        int choose = root->val + left.second + right.second;
        int unchoose = max(left.first, left.second) + max(right.first, right.second);
        return { choose, unchoose };
    }

   public:
    int rob(TreeNode* root) {
        pair<int, int> res = dfs(root);
        return max(res.first, res.second);
    }
};