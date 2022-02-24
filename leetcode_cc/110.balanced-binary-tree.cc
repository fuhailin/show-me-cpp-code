#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    int getDepth(TreeNode* root) {
        if (root) {
            int left = getDepth(root->left);
            int right = getDepth(root->right);
            return 1 + max(left, right);
        }
        return 0;
    }

   public:
    bool isBalanced(TreeNode* root) {
        if (root) {
            int left = getDepth(root->left);
            int right = getDepth(root->right);
            if (abs(left - right) <= 1) {
                return isBalanced(root->left) && isBalanced(root->right);
            }
            return false;
        }
        return true;
    }
};