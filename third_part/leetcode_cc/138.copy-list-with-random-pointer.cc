#include <unordered_map>
// Definition for a Node.
class Node {
   public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
   public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }
        unordered_map<Node*, Node*> mymap;
        Node* cur = head;
        while (cur) {
            mymap[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        while (cur) {
            mymap[cur]->next = mymap[cur->next];
            mymap[cur]->random = mymap[cur->random];
            cur = cur->next;
        }
        return mymap[head];
    }
};