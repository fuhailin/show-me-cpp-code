#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode;

//��������
LNode* Create(void)
{
	LNode *Head, *current;
	Head = current = (LNode *)malloc(sizeof(LNode));
	Head->next = NULL;

	ElemType d;
	LNode *temp;
	char s;
	while (1)
	{
		temp = (LNode *)malloc(sizeof(LNode)); //Ϊ�½ڵ�����ڴ�ռ�
		scanf("%d", &temp->data);
		current->next = temp;
		current = temp;
		s = getchar();           //s���������Ƿ��ǻس�  
		if (s == '\n') { break; }
	}
	current->next = NULL;  //���βָ��ΪNULL
	return Head;
}

//�������
void List(LNode *L)
{
	LNode *p;
	p = L->next;  //
	while (p != NULL)
	{
		printf("%2d", p->data);
		p = p->next;
	}
}

void Merge(LNode *&A, LNode *&B, LNode *&C)
{
	LNode *p, *q, *current;
	p = A->next;
	q = B->next;
	free(B);
	C = A;
	C->next = NULL;
	current = C;
	while (p != NULL && q != NULL)
	{
		if (p->data <= q->data)
		{
			current->next = p;
			p = p->next;
			current = current->next;
		}
		else
		{
			current->next = q;
			q = q->next;
			current = current->next;
		}
	}
	current->next = NULL;
	if (p != NULL)
	{
		current->next = p;
	}
	if (q != NULL)
	{
		current->next = q;
	}
}

int main2()
{
	LNode *L1, *L2,*L3;
	printf("�������1������:\n");
	L1 = Create();
	printf("\n�������2������:\n");
	L2 = Create();
	Merge(L1, L2, L3);
	printf("�ϲ��������Ϊ:\n");
	List(L3);
	system("pause");
	return 0;
}
