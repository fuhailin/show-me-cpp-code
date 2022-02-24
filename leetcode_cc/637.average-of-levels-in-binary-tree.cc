#include <queue>
#include <vector>

#include "include/TreeNode.h"
using namespace std;

class Solution {
   public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> myque;
        if (!root) {
            return res;
        }
        myque.push(root);
        while (!myque.empty()) {
            int size = myque.size();
            double sum = 0;
            for (int i = 0; i < size; i++) {
                TreeNode* node = myque.front();
                myque.pop();
                sum += 1.0 * node->val;
                if (node->left) myque.push(node->left);
                if (node->right) myque.push(node->right);
            }
            res.push_back(sum / size);
        }
        return res;
    }
};