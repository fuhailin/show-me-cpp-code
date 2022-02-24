#include "include/LinkedList.h"

class Solution {
    // 翻转一个子链表，并且返回新的头与尾
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail) {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

   public:
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        ListNode* hair = new ListNode(0);
        hair->next = head;
        ListNode* pre = hair;

        int k = 1, len;
        while (head) {
            ListNode* tail = pre;
            len = 0;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                if (!tail->next) {
                    // cout << "len here = " << len << endl;
                    if(len % 2 == 0){
                        tie(head, tail) = myReverse(head, tail);
                    }
                    // 把子链表重新接回原链表
                    pre->next = head;
                    tail->next = nullptr;
                    pre = tail;
                    head = tail->next;
                    return hair->next;
                } else {
                    tail = tail->next;
                    len++;
                }
            }
            nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            if(len % 2 == 0){
                tie(head, tail) = myReverse(head, tail);
            }
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
            k++;
        }


        return hair->next;

    }
};


head = [5,2,6,3,9,1,7,3,8,4]
输出：[5,6,2,3,9,1,4,8,3,7]

[5,6,2,3,9,1,4,8,3,7]
[1,0,1,6]
[2,1]
[8]