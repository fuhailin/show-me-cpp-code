class Solution {
  vector<int> _inorder;
  vector<int> _preorder;

  void inorder(TreeNode *root) {
    if (root != nullptr) {
      inorder(root->left);
      _inorder.push_back(root->val);
      inorder(root->right);
    }
  }

  void preorder(TreeNode *root) {
    if (root != nullptr) {
      _preorder.push_back(root->val);
      preorder(root->left);
      preorder(root->right);
    }
  }

public:
  string getDirections(TreeNode *root, int startValue, int destValue) {
    inorder(root);
    preorder(root);
    int parentIdx;
    for (int i = 0; i < _inorder.size(); i++) {
      if (_inorder[i] == root->val) {
        parentIdx = i;
        break;
      }
    }
    string res;
    bool flag = false;
    for (int i = 0; i < _inorder.size(); i++) {
      if (_inorder[i] == startValue) {
        flag = true;
      } else {
        if (flag){
            if(i < parentIdx) {
                res += "U";
            }
        }
      }
    }
  }
};