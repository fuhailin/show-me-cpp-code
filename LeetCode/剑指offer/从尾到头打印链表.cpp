#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef int ElemType;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
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

	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> res;
		if (head == NULL)
			return res;
		stack<int> stack;
		ListNode *p = head->next;
		while (p != NULL)
		{
			stack.push(p->val);
			p = p->next;
		}
		while (!stack.empty())
		{
			res.push_back(stack.top());
			stack.pop();
		}
		return res;
	}

};

int main3()
{
	printf("�������1������:\n");
	ListNode *L1 = Solution().Create();
	vector<int> test = Solution().printListFromTailToHead(L1);
	system("pause");
}