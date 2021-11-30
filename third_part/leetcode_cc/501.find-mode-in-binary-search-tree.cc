#include <vector>

#include "include/TreeNode.h"

using namespace std;

class Solution {
    int base, count = 0, maxCount = INT_MIN;
    vector<int> res;
    void dfs(TreeNode* root) {
        if (!root) {
            return;
        }
        dfs(root->left);
        if (base == root->val) {
            count++;
        } else {
            base = root->val;
            count = 1;
        }
        if(count == maxCount){
            res.push_back(base);
        }
        if(count > maxCount){
            maxCount = count;
            res = vector<int> {base};
        }
        dfs(root->right);
    }

   public:
    vector<int> findMode(TreeNode* root) {
        dfs(root);
        return res;
    }
};