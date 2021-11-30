#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
   public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty()) return nullptr;
        int len = inorder.size();
        int root_val = postorder[len - 1];
        int idx;
        for (idx = 0; idx < len - 1; ++idx) {
            if (inorder[idx] == root_val) {
                break;
            }
        }
        vector<int> inleft = {inorder.begin(), inorder.begin() + idx};
        vector<int> inright = {inorder.begin() + idx + 1, inorder.end()};
        vector<int> postleft = {postorder.begin(), postorder.begin() + inleft.size()};
        vector<int> postright = {postorder.begin() + inleft.size(), postorder.end() - 1};

        TreeNode* root = new TreeNode(root_val);
        root->left = buildTree(inleft, postleft);
        root->right = buildTree(inright, postright);
        return root;
    }
};