#include <math.h>

#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    int minDepth(TreeNode* root) {
        int depth = 0;
        queue<TreeNode*> myque;
        if (!root) {
            return 0;
        }
        myque.push(root);
        while (!myque.empty()) {
            depth++;
            int size = myque.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = myque.front();
                myque.pop();
                if (node->left) myque.push(node->left);
                if (node->right) myque.push(node->right);
                if (!node->left && !node->right) break;
            }
        }
        return depth;
    }
};