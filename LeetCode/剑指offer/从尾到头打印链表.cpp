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
	printf("请输入第1个链表:\n");
	ListNode *L1 = Solution().Create();
	vector<int> test = Solution().printListFromTailToHead(L1);
	system("pause");
}