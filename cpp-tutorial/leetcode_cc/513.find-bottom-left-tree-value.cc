#include <queue>

#include "include/TreeNode.h"

using namespace std;

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> myque;
        if (root) {
            myque.push(root);
        }
        int res = 0;
        while (!myque.empty()) {
            int size = myque.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = myque.front();
                myque.pop();
                if(i == 0) res = node->val;
                if (node->left) myque.push(node->left);
                if (node->right) myque.push(node->right);
            }
        }
        return res;
    }
};