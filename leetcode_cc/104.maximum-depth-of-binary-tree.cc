#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    int maxDepth(TreeNode* root) {
        if (root) {
            int left = maxDepth(root->left);
            int right = maxDepth(root->right);
            return 1 + max(left, right);
        }
        return 0;
    }
};