#include <iostream>
#include <vector>

#include "include/TreeNode.h"
using namespace std;

class Solution {
    vector<TreeNode*> backtracking(int start, int end) {
        if (start > end) return {nullptr};
        vector<TreeNode*> allTree;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> leftTree = backtracking(start, i - 1);
            vector<TreeNode*> rightTree = backtracking(i + 1, end);
            for (TreeNode* left : leftTree) {
                for (TreeNode* right : rightTree) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    allTree.emplace_back(root);
                }
            }
        }
        return allTree;
    }

   public:
    vector<TreeNode*> generateTrees(int n) {
        return backtracking(1, n);
    }
};