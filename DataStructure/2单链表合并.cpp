#include <iostream>
using namespace std;

typedef int ElemType;
struct LNode
{
	ElemType data;
	struct LNode *next;
};

//创建链表
LNode *Create(void)
{
	LNode *Head, *current;
	// Head = current = (LNode *)malloc(sizeof(LNode));
	Head = current = new LNode();
	Head->next = NULL;

	ElemType d;
	LNode *temp;
	char s;
	while (1)
	{
		temp = new LNode();
		// temp = (LNode *)malloc(sizeof(LNode)); //为新节点分配内存空间
		cin >> &temp->data;
		// scanf("%d", &temp->data);
		current->next = temp;
		current = temp;
		s = getchar(); //s用来接收是否是回车
		if (s == '\n')
		{
			break;
		}
	}
	current->next = NULL; //最后尾指针为NULL
	return Head;
}

//输出链表
void List(LNode *L)
{
	LNode *p;
	p = L->next; //
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

int main()
{
	LNode *L1, *L2, *L3;
	printf("请输入第1个链表:\n");
	L1 = Create();
	printf("\n请输入第2个链表:\n");
	L2 = Create();
	Merge(L1, L2, L3);
	printf("合并后的链表为:\n");
	List(L3);
	return 0;
}
