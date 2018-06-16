#include<iostream>
using namespace std;
typedef int ElemType;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

//创建链表
ListNode* Create(void)
{
	ListNode *Head, *current;
	Head = current = (ListNode *)malloc(sizeof(ListNode));
	Head->next = NULL;

	ElemType d;
	ListNode *temp;
	char s;
	while (1)
	{
		temp = (ListNode *)malloc(sizeof(ListNode)); //为新节点分配内存空间
		scanf("%d", &temp->val);
		current->next = temp;
		current = temp;
		s = getchar();           //s用来接收是否是回车  
		if (s == '\n') { break; }
	}
	current->next = NULL;  //最后尾指针为NULL
	return Head;
}

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{

}
int main()
{
	system("pause");
	return 0;
}