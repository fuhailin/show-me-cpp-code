#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (!root)
        {
            return nullptr;
        }
        if(root->val < low){
            root = root->right;
            root = trimBST(root, low, high);
        } else if (root->val > high)
        {
            root = root->left;
            root = trimBST(root, low, high);
        } else {
            root->left = trimBST(root->left, low, high);
            root->right = trimBST(root->right, low, high);
        }
        return root;
    }
};