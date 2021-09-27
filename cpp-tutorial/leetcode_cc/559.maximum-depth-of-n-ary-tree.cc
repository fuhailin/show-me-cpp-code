#include <vector>
using namespace std;

// Definition for a Node.
class Node {
   public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
   public:
    int maxDepth(Node* root) {
        int depth = 0;
        if (root) {
            for (auto& child : root->children) {
                depth = max(maxDepth(child), depth);
            }
            return depth + 1;
        }
        return depth;
    }
};