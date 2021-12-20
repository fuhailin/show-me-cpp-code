#include "include/TreeNode.h"

class Solution {
    int result;
    int dfs(TreeNode* root)
    {
        // 0：该节点无覆盖
        // 1：本节点有摄像头
        // 2：本节点有覆盖
        if (!root)
            return 2;

        int left = dfs(root->left);
        int right = dfs(root->right);

        if (left == 0 || right == 0) {
            result++;
            return 1;
        } else if (left == 1 || right == 1) {
            return 2;
        } else {
            return 0;
        }
    }

public:
    int minCameraCover(TreeNode* root)
    {
        if (dfs(root) == 0) {
            result++;
        }
        return result;
    }
};