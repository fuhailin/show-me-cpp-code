/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root==NULL)
            return true;
        if(abs(getDepth(root->left) - getDepth(root->right)) <=1)
            return isBalanced(root->left) && isBalanced(root->right);
        else
            return false;
    }
    int getDepth(TreeNode* root)
    {
        if(root==NULL)
            return 0;
        else
            return max(getDepth(root->left), getDepth(root->right)) + 1;
    }
};