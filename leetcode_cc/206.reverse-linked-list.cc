#include "include/LinkedList.h"

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr, *cur = head, *next = nullptr;
        while (cur)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};