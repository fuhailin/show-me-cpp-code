#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> myque;
        if (!root) {
            return res;
        }
        myque.push(root);
        while (!myque.empty()) {
            int size = myque.size();
            vector<int> level;
            for (int i = 0; i < size; i++) {
                TreeNode* node = myque.front();
                myque.pop();
                level.push_back(node->val);
                if (node->left) myque.push(node->left);
                if (node->right) myque.push(node->right);
            }
            res.emplace_back(level);
        }
        return res;
    }
};