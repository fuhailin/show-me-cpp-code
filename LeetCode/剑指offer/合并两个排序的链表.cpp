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

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{

}
int main()
{
	system("pause");
	return 0;
}