#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;

typedef int ElemType;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

//��������
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
		temp = (ListNode *)malloc(sizeof(ListNode)); //Ϊ�½ڵ�����ڴ�ռ�
		scanf("%d", &temp->val);
		current->next = temp;
		current = temp;
		s = getchar();           //s���������Ƿ��ǻس�  
		if (s == '\n') { break; }
	}
	current->next = NULL;  //���βָ��ΪNULL
	return Head;
}
//�������
void List(ListNode *L)
{
	ListNode *p;
	p = L->next;  //
	while (p != NULL)
	{
		printf("%2d", p->val);
		p = p->next;
	}
}
ListNode* ReverseList(ListNode* pHead) {
	if (pHead == nullptr)
		return nullptr;
	stack<int> S;
	ListNode *p = pHead, *q = pHead, *newHead = pHead;
	while (p!=nullptr)
	{
		S.push(p->val);
		p = p->next;
	}
	while (!S.empty())
	{
		q->val = S.top();
		S.pop();
		q = q->next;
	}
	return newHead;
}

int main()
{
	ListNode *L1;
	printf("�������1������:\n");
	L1 = Create();

	ListNode *tmp = ReverseList(L1);
	List(tmp);
	system("pause");
	return 0;
}