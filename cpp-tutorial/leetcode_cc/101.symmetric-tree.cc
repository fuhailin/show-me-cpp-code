#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    bool compare(TreeNode* left, TreeNode* right) {
        if (!left && !right)
            return true;
        else if (!left && right)
            return false;
        else if (left && !right)
            return false;
        else {
            if (left->val == right->val)
                return compare(left->left, right->right) && compare(left->right, right->left);
            else
                return false;
        }
    }

   public:
    bool isSymmetric(TreeNode* root) {
        if (root) {
            return compare(root->left, root->right);
        }
        return true;
    }
};