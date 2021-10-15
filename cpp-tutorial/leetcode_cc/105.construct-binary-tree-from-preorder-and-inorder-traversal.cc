#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (inorder.empty() || preorder.empty()) return nullptr;
        int len = inorder.size();
        int root_val = preorder[0];
        int idx;
        for (idx = 0; idx < len - 1; ++idx) {
            if (inorder[idx] == root_val) {
                break;
            }
        }
        vector<int> inleft = {inorder.begin(), inorder.begin() + idx};
        vector<int> inright = {inorder.begin() + idx + 1, inorder.end()};
        vector<int> preleft = {preorder.begin() + 1, preorder.begin() + inleft.size() + 1};
        vector<int> preright = {preorder.end() - inright.size(), preorder.end()};

        TreeNode* root = new TreeNode(root_val);
        root->left = buildTree(preleft, inleft);
        root->right = buildTree(preright, inright);
        return root;
    }
};