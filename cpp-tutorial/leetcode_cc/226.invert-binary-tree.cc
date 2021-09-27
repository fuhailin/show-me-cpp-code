#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root){
            TreeNode* left = invertTree(root->left);
            TreeNode* right = invertTree(root->right);
            root->left = right;
            root->right = left;
            return root;
        }
        return nullptr;
    }
};