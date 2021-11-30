#include <queue>
#include <vector>

#include "include/TreeNode.h"

using namespace std;


class Solution {
    int sum;

public:
    TreeNode* convertBST(TreeNode* root) {
        if(root){
            convertBST(root->right);
            sum += root->val;
            root->val = sum;
            convertBST(root->left);
        }
        return root;
    }
};