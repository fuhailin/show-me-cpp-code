#include <iostream>
using namespace std;
typedef int ElemType;
//  Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
  public:
    ListNode *mergeTwoLists1(ListNode *l1, ListNode *l2)
    {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists1(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists1(l1, l2->next);
            return l2;
        }
    }

    ListNode *mergeTwoLists2(ListNode *l1, ListNode *l2)
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
    ListNode *Create(void)
    {
        ListNode head(-1); //, *current;
        // Head = current = (ListNode *)malloc(sizeof(ListNode));
        // Head->next = NULL;

        ElemType d;
        ListNode *tail = &head;
        char s;
        while (1)
        {
            cin >> d;
            ListNode *temp = new ListNode(d);
            tail->next = temp;
            tail = tail->next;
            s = getchar(); //s用来接收是否是回车
            if (s == '\n')
            {
                break;
            }
        }
        return head.next;
    }
    //输出链表
    void Print_List(ListNode *L)
    {
        ListNode *p;
        p = L; //
        while (p != NULL)
        {
            cout << p->val << " ";
            p = p->next;
        }
    }
};

int main(int argc, char const *argv[])
{
    Solution solu;
    ListNode *L1, *L2, *L3;
    cout << "请输入第1个链表:\n";
    L1 = solu.Create();
    cout << "\n请输入第2个链表:" << endl;
    L2 = solu.Create();
    L3 = solu.mergeTwoLists2(L1, L2);
    cout << "合并后的链表为:" << endl;
    solu.Print_List(L3);
    return 0;
}
