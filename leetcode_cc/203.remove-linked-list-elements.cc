#include "include/LinkedList.h"

class Solution {
   public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* hat = new ListNode(0);
        hat->next = head;
        ListNode *fast = head, *slow = hat;
        while (fast) {
            if (fast->val == val) {
                ListNode* tmp = fast;
                slow->next = fast->next;
                fast = fast->next;
                delete tmp;
            } else {
                slow = slow->next;
                fast = fast->next;
            }
        }
        return hat->next;
    }
};