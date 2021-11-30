#include <queue>
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
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        queue<Node*> myque;
        if (!root) {
            return res;
        }
        myque.push(root);
        while (!myque.empty()) {
            int size = myque.size();
            vector<int> level;
            for (int i = 0; i < size; i++) {
                Node* node = myque.front();
                myque.pop();
                level.push_back(node->val);
                for (auto& kid : node->children) {
                    myque.push(kid);
                }
            }
            res.emplace_back(level);
        }
        return res;
    }
};