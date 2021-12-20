#include "include/LinkedList.h"

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;

        Node * cur = head;
        while (cur)
        {
            Node * tmp = new Node(cur->val);
            tmp->next = cur->next;
            cur->next = tmp;
            cur = tmp->next;
        }

        cur = head;
        while (cur)
        {
            Node * tmp = cur->next;
            if(cur->random){
                tmp->random = cur->random->next;
            }
            cur = tmp->next;
        }

        cur = head->next;
        Node * hat = new Node(0);
        hat->next = cur;
        Node * ori = head;
        while (ori && cur)
        {
            ori->next = cur->next;
            ori = ori->next;
            if(ori){
                cur->next = ori->next;
            } else {
                cur->next = nullptr;
            }
            cur = cur->next;
        }
        return hat->next;
    }
};