#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        int idx = 1;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            if (idx == k) {
                break;
            }
            idx++;
            stk.pop();
            root = root->right;
        }
        return root->val;
    }
};