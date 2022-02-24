#include <vector>

#include "include/TreeNode.h"
using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void backtracking(TreeNode *root, int targetSum) {
        if (targetSum == root->val && !root->left && !root->right) {
            path.push_back(root->val);
            res.emplace_back(path);
            path.pop_back();
            return;
        }
        if (root->left) {
            path.push_back(root->val);
            backtracking(root->left, targetSum - root->val);
            path.pop_back();
        }
        if (root->right) {
            path.push_back(root->val);
            backtracking(root->right, targetSum - root->val);
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        if (root) {
            backtracking(root, targetSum);
        }
        return res;
    }
};