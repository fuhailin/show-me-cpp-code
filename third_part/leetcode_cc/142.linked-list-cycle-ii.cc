#include <gtest/gtest.h>

#include <vector>

#include "include/LinkedList.h"

class Solution {
   public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;
        ListNode *slow = head, *fast = head;
        do {
            if (!fast->next || !fast->next->next) return nullptr;
            fast = fast->next->next;
            slow = slow->next;
        } while (fast != slow);
        slow = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main(int argc, const char **argv) {
    ListNode *test = new ListNode(3);
    ListNode *test1 = new ListNode(2);
    ListNode *test2 = new ListNode(0);
    ListNode *test3 = new ListNode(-4);
    test->next = test1;
    test1->next = test2;
    test2->next = test3;
    test3->next = test1;

    Solution s;
    ListNode *ret = s.detectCycle(test);
    std::cout << "res " << ret->val << std::endl;
    return 0;
}