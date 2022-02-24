#include "include/LinkedList.h"

class Solution {
    
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* hat = new ListNode(-1);
        hat->next = head;
        ListNode* tmp = hat, *node1, *node2;
        while (tmp->next != nullptr && tmp->next->next != nullptr)
        {
            node1 = tmp->next;
            node2 = tmp->next->next;
            node1->next = node2->next;
            node2->next = node1;
            tmp->next = node2;
            tmp = node1;
        }
        return hat->next;
    }
};