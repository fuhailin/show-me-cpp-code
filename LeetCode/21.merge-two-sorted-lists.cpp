#include "../DataStructure/LinkedList.h"
#include <iostream>
#include <string>
using namespace std;
typedef int ElemType;

class Solution
{
  public:
    ListNode *mergeTwoLists_recursive(ListNode *l1, ListNode *l2)
    {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists_recursive(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists_recursive(l1, l2->next);
            return l2;
        }
    }

    ListNode *mergeTwoLists_iterative(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(-1);
        ListNode *tail = &dummy;
        while (l1 != NULL && l2 != NULL)
        {
            if (l1->val < l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 == NULL ? l2 : l1;
        return dummy.next;
    }

    //创建链表
    void Create(LinkedList &list)
    {
        while (1)
        {
            int temp;
            cin >> temp;
            list.addNode(temp);
            char s = cin.get(); //s用来接收是否是回车
            if (s == '\n')
            {
                break;
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Solution solu;
    LinkedList L1, L2, L3;
    cout << "请输入第1个链表:\n";
    solu.Create(L1);
    cout << "\n请输入第2个链表:" << endl;
    solu.Create(L2);
    L3.head = solu.mergeTwoLists_iterative(L1.head, L2.head);
    cout << "合并后的链表为:" << endl;
    L3.display();
    return 0;
}
