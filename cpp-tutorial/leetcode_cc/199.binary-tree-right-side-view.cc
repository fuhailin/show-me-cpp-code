#include <queue>
#include <vector>

#include "include/TreeNode.h"
using namespace std;

class Solution {
    vector<int> res;
    void dfs(TreeNode* root, int depth) {
        if (depth == res.size()) {
            res.push_back(root->val);
        }
        depth++;
        if (root->right) dfs(root->right, depth);
        if (root->left) dfs(root->left, depth);
    }

   public:
    vector<int> rightSideView(TreeNode* root) {
        if (root) {
            dfs(root, 0);
        }
        return res;
    }
};