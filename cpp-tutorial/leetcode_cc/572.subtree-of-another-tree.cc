#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        else if (!p || !q)
            return false;
        else {
            return p->val == q->val ? isSameTree(p->left, q->left) && isSameTree(p->right, q->right) : false;
        }
    }

   public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root && !subRoot)
            return true;
        else if (!root || !subRoot)
            return false;
        else {
            return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
        }
    }
};