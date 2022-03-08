
#include <vector>
using namespace std;

// /*
// Definition for a Node.
class Node {
 public:
  int val;
  Node* left;
  Node* right;

  Node() {}

  Node(int _val) {
    val = _val;
    left = NULL;
    right = NULL;
  }

  Node(int _val, Node* _left, Node* _right) {
    val = _val;
    left = _left;
    right = _right;
  }
};
// */

class Solution {
  Node *prev, *now, *head;
  void inOrder(Node* root) {
    if (root == nullptr) {
      return;
    }
    inOrder(root->left);
    if (!head) head = root;
    prev = now;
    now = root;
    if (prev != nullptr) {
      prev->right = now;
      now->left = prev;
    }
    inOrder(root->right);
  }

 public:
  Node* treeToDoublyList(Node* root) {
    if (root == NULL) return root;
    inOrder(root);
    // 最后一个 now 节点就是尾节点
    // 头尾节点建立关系
    head->left = now;
    now->right = head;
    return head;
  }
};