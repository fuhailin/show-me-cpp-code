#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        else if (!p || !q)
            return false;
        else {
            return p->val == q->val ? isSameTree(p->left, q->left) && isSameTree(p->right, q->right) : false;
        }
    }
};