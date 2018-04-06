//LeetCode 203. 删除链表中的元素
#include <iostream>
using namespace std;

typedef int ElemType;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {

		if (head == NULL) 
			return NULL;
		ListNode *next = removeElements(head->next, val);
		if (head->val == val) 
			return next;
		else
		{
			head->next = next;
			return head;
		}
	}

	//ListNode* removeElements1(ListNode* head, int val) {

	//	if (head == NULL)
	//		return NULL;
	//	if (head->val == val)
	//		head->next = head->next->next;
	//	return removeElements(head->next, val);
	//	else
	//	{
	//	ListNode *tmp = head;
	//	while (tmp->next != NULL)
	//	{
	//	if (tmp->next->val == val)
	//	{
	//	tmp->next = tmp->next->next;
	//	tmp = tmp->next;
	//	if (tmp == NULL)
	//	return head;
	//	}
	//	else
	//	{
	//	tmp = tmp->next;
	//	}
	//	}
	//	return head;
	//	}
	//}

	//创建无头结点的单链表
	ListNode* Create(void)
	{
		char s;
		ListNode *tail = NULL;
		ListNode *head = NULL;
		while (1)
		{

			ListNode *tmp = new ListNode(0);     //定义一个s节点用来存放每次要输入的值
			scanf("%d", &tmp->val);

			if (head == NULL)
			{
				head = tmp;
			}
			else
			{
				tail->next = tmp;
			}
			tail = tmp;
			s = getchar();
			if (s == '\n') { break; }
		}
		if (tail != NULL)
			tail->next = NULL;
		return head;
	}
	//输出无头结点单链表
	void List(ListNode *L)
	{
		ListNode *p;
		p = L;  //
		while (p != NULL)
		{
			printf("%2d", p->val);
			p = p->next;
		}
	}
};





int main3()
{
	ListNode *L1;
	int temp;
	printf("请输入链表:\n");
	L1 = Solution().Create();
	printf("\n请输入要移除的元素:\n");
	scanf("%d", &temp);
	ListNode* ret = Solution().removeElements(L1, temp);
	printf("移除后的链表为:\n");
	Solution().List(L1);
	system("pause");
	return 0;
}
