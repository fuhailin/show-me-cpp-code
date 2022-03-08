#include <unordered_set>

#include "bits/stdc++.h"
#include "include/TreeNode.h"

class Solution {
  int findRoot(vector<vector<int>>& descriptions) {
    unordered_set<int> children;
    for (vector<int>& subTree : descriptions) {
      children.emplace(subTree[1]);
    }

    for (vector<int>& subTree : descriptions) {
      if (children.find(subTree[0]) == children.end()) {
        return subTree[0];
      }
    }
    return 0;
  }

 public:
  TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
    unordered_map<int, TreeNode*> dict;
    for (vector<int>& subTree : descriptions) {
      if (dict.find(subTree[0]) == dict.end()) {
        dict.emplace(subTree[0], new TreeNode(subTree[0]));
      }

      if (dict.find(subTree[1]) == dict.end()) {
        dict.emplace(subTree[1], new TreeNode(subTree[1]));
      }
      if (subTree[2] == 1) {
        dict[subTree[0]]->left = dict[subTree[1]];
      } else {
        dict[subTree[0]]->right = dict[subTree[1]];
      }
    }
    int root = findRoot(descriptions);
    return dict[root];
  }
};
