#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> myque;
        if (!root) {
            return res;
        }
        myque.push(root);
        while (!myque.empty()) {
            int size = myque.size();
            int level = INT_MIN;
            for (int i = 0; i < size; i++) {
                TreeNode* node = myque.front();
                myque.pop();
                level = max(level, node->val);
                if (node->left) myque.push(node->left);
                if (node->right) myque.push(node->right);
            }
            res.emplace_back(level);
        }
        return res;
    }
};