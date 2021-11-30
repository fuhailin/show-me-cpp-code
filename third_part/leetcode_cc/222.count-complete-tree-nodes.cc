#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};