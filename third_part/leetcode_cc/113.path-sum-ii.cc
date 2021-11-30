#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 *  */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void backtracking(TreeNode *root, int targetSum){
        if(targetSum == root->val && !root->left && !root->right){
            path.push_back(root->val);
            res.emplace_back(path);
            path.pop_back();
            return;
        }
        if(root->left){
            path.push_back(root->val);
            backtracking(root->left, targetSum - root->val);
            path.pop_back();
        }
        if(root->right){
            path.push_back(root->val);
            backtracking(root->right, targetSum - root->val);
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        if(root) {
            backtracking(root, targetSum);
        }
        return res;
    }
};