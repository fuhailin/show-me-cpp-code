#include <string>
#include <vector>

#include "include/TreeNode.h"

class Solution {
   public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        if (root->val == key) {
            if (!root->left && !root->right) {
                return nullptr;
            } else if (root->left && !root->right) {
                return root->left
            } else if (!root->left && root->right) {
                return root->right;
            } else {
                TreeNode* cur = root->right;
                while (cur->left) {
                    cur = cur->left;
                }
                cur->left = root->left;
                TreeNode* tmp = root;
                root = root->right;
                delete tmp;
                return root;
            }
        }
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
};