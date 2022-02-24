#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    vector<int> order;
    void inorder(TreeNode* root) {
        if (root) {
            inorder(root->left);
            order.push_back(root->val);
            inorder(root->right);
        }
    }

   public:
    int getMinimumDifference(TreeNode* root) {
        inorder(root);
        int n = order.size();
        if (n <= 1) return 0;
        int res = INT_MAX;
        for (int i = 1; i < n; i++) {
            res = min(res, order[i] - order[i - 1]);
        }
        return res;
    }
};