#include <string>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    vector<string> res;

    void backtracking(TreeNode* node, string path) {
        if (!node->left && !node->right) {
            res.push_back(path + to_string(node->val));
            return;
        }
        if (node->left) {
            backtracking(node->left, path + to_string(node->val) + "->");
        }
        if (node->right) {
            backtracking(node->right, path + to_string(node->val) + "->");
        }
    }

   public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root) {
            string path;
            backtracking(root, path);
        }
        return res;
    }
};