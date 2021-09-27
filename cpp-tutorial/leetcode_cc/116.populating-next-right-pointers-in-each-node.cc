#include <queue>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
   public:
    Node* connect(Node* root) {
        queue<Node*> myque;
        if (!root) {
            return root;
        }
        myque.push(root);
        while (!myque.empty()) {
            int size = myque.size();
            for (int i = 0; i < size; i++) {
                Node* node = myque.front();
                myque.pop();
                if (i == size - 1) {
                    node->next = NULL;
                } else {
                    node->next = myque.front();
                }
                if (node->left) myque.push(node->left);
                if (node->right) myque.push(node->right);
            }
        }
        return root;
    }
};