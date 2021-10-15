#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    vector<int> order;
    void inorder(TreeNode* root) {
        if (root) {
            inorder(root->left);
            order.push_back(root->val);
            inorder(root->right);
        }
    }

   public:
    bool isValidBST(TreeNode* root) {
        inorder(root);
        int n = order.size();
        if(n <= 1) return true;
        for(int i = 1; i < n; i++){
            if(order[i - 1] >= order[i]){
                return false;
            }
        }
        return true;
    }
};