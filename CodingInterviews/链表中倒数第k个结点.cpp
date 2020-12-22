#include<stdio.h>
#include<iostream>
#include<string>
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

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
	if (k == 0||pListHead==nullptr)
		return nullptr;
	ListNode *p = pListHead, *q = pListHead;
	for (int i = 0; i < k-1; i++)
	{
		if (p->next == nullptr)
			return nullptr;
		else
		{
			p = p->next;
		}
	}
	while (p->next!=nullptr)
	{
		p = p->next;
		q = q->next;
	}
	return q;
}

int main14()
{
	int k;
	cin >> k;
	ListNode *L1, *L2, *L3;
	printf("�������1������:\n");
	L1 = Create();

	ListNode *tmp=FindKthToTail(L1, k);
	if (tmp == NULL)
		cout << "NULL" << endl;
	else
	{
		cout << tmp->val << endl;
	}
	system("pause");
	return 0;
}