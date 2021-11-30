#include <string>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    int res = 0;
    void dfs(TreeNode* node) {
        if (node) {
            if (node->left) {
                if (!node->left->left && !node->left->right) {
                    res += node->left->val;
                } else {
                    dfs(node->left);
                }
            }
            dfs(node->right);
        } else {
            return;
        }
    }

   public:
    int sumOfLeftLeaves(TreeNode* root) {
        dfs(root);
        return res;
    }
};