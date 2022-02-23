#include <stdio.h>
#include <iostream>
using namespace std;
typedef int ElemType;

struct ListNode
{
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL)
	{
	}
};

void PrintList(ListNode *pHead)
{
	ListNode *pNode = pHead;
	while (pNode != NULL)
	{
		cout << pNode->val << " ";
		pNode = pNode->next;
	}
}

//创建无头结点单链表
ListNode *Create(void)
{
	ListNode *head, *tail;
	head = NULL;
	tail = head;
	ElemType d;
	char s;
	while (1)
	{
		//scanf("%d", &d);
		cin >> d;
		ListNode* temp = new ListNode(d); //initialized root
		if (tail == NULL)
		{
			head = temp;
			tail = head;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		s = getchar();           //s用来接收是否是回车  
		if (s == '\n') { break; }
	}
	return head;
}

ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
{
	if (pHead1 == NULL)
		return pHead2;
	else if (pHead2 == NULL)
		return pHead1;
	ListNode *pMergeHead = NULL;
	if (pHead1->val < pHead2->val)
	{
		pMergeHead = pHead1;
		pMergeHead->next = Merge(pHead1->next, pHead2);
	}
	else
	{
		pMergeHead = pHead2;
		pMergeHead->next = Merge(pHead1, pHead2->next);
	}
	return pMergeHead;
}
int main()
{

	printf("input the 1st List:\n");
	ListNode *L1 = Create();
	printf("input the 2nd List:\n");
	ListNode *L2 = Create();
	ListNode *L3 = Merge(L1, L2);
	PrintList(L3);

	return 0;
}
