#include <unordered_map>

#include "include/TreeNode"

class Solution {
  unordered_map<int, int> hashmap;
  int target;
  int dfs(TreeNode* root, int curSum) {
    if (root == nullptr) {
      return 0;
    }
    int res = 0;
    curSum += root->val;
    if (hashmap.find(curSum - target) != hashmap.end()) {
      res += hashmap[curSum - target];
    }
    hashmap[curSum]++;
    res += dfs(root->left, curSum);
    res += dfs(root->right, curSum);
    hashmap[curSum]--;
    return res;
  }

 public:
  int pathSum(TreeNode* root, int targetSum) {
    hashmap[0] = 1;
    target = targetSum;
    return dfs(root, 0);
  }
};