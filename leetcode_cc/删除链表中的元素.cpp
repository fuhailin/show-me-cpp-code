// LeetCode 203. ɾ�������е�Ԫ��
#include <iostream>
using namespace std;

typedef int ElemType;
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* removeElements(ListNode* head, int val) {
    if (head == NULL) return NULL;
    ListNode* next = removeElements(head->next, val);
    if (head->val == val)
      return next;
    else {
      head->next = next;
      return head;
    }
  }

  // ListNode* removeElements1(ListNode* head, int val) {

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

  //������ͷ���ĵ�����
  ListNode* Create(void) {
    char s;
    ListNode* tail = NULL;
    ListNode* head = NULL;
    while (1) {
      ListNode* tmp = new ListNode(0);  //����һ��s�ڵ��������ÿ��Ҫ�����ֵ
      scanf("%d", &tmp->val);

      if (head == NULL) {
        head = tmp;
      } else {
        tail->next = tmp;
      }
      tail = tmp;
      s = getchar();
      if (s == '\n') {
        break;
      }
    }
    if (tail != NULL) tail->next = NULL;
    return head;
  }
  //�����ͷ��㵥����
  void List(ListNode* L) {
    ListNode* p;
    p = L;  //
    while (p != NULL) {
      printf("%2d", p->val);
      p = p->next;
    }
  }
};

int main3_1() {
  ListNode* L1;
  int temp;
  printf("����������:\n");
  L1 = Solution().Create();
  printf("\n������Ҫ�Ƴ���Ԫ��:\n");
  scanf("%d", &temp);
  ListNode* ret = Solution().removeElements(L1, temp);
  printf("�Ƴ��������Ϊ:\n");
  Solution().List(L1);
  system("pause");
  return 0;
}
