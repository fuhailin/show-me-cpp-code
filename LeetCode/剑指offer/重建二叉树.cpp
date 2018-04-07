#include <iostream>
#include <vector>
using namespace std;

 //Definition for binary tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution
{
public:

	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		int vinlen = vin.size();
		if (pre.size() == 0|| vinlen ==0)
			return NULL;
		vector<int> left_pre, right_pre, left_vin, right_vin;
		//�������ڵ㣬���ڵ�϶���ǰ������ĵ�һ����
		TreeNode* root = new TreeNode(pre[0]);

		//�ҵ�����������ڵ�����λ��,����ڱ���gen��
		int rootIndex = 0;

		for (int i = 0; i < vinlen; i++)
		{
			if (vin[i] == pre[0])
			{
				rootIndex = i;
				break;
			}
		}

		//����������������ڵ���ߵĽڵ�λ�ڶ���������ߣ����ڵ��ұߵĽڵ�λ�ڶ��������ұ�
		//����������㣬�Զ������ڵ���й鲢
		for (int i = 0; i < rootIndex; i++)
		{
			left_vin.push_back(vin[i]);
			left_pre.push_back(pre[i + 1]);//ǰ���һ��Ϊ���ڵ�
		}
		for (int i = rootIndex + 1; i < vinlen; i++)
		{
			right_vin.push_back(vin[i]);
			right_pre.push_back(pre[i]);
		}

		//��shell�����˼�����ƣ�ȡ��ǰ�������������ڵ���ߺ��ұߵ�����
		//�ݹ飬�ٶ�������������в��裬��������������������������ֱ��Ҷ�ڵ�
		root->left = reConstructBinaryTree(left_pre, left_vin);
		root->right = reConstructBinaryTree(right_pre, right_vin);
		return root;
	}

	void postorder(TreeNode *p)
	{
		if (p != NULL)
		{
			postorder(p->left);
			postorder(p->right);
			visit(p);
		}
	}
	void visit(TreeNode* node)
	{
		printf("%d", node->val);// %c ����ַ��ͱ���
	}

private:

};

int main4()
{
	printf("�������1������:\n");
	vector<int> preorder = { 1,2,4,7,3,5,6,8 };
	vector<int> midorder = { 4,7,2,1,5,3,8,6 };

	TreeNode* BTTree = Solution().reConstructBinaryTree(preorder,midorder);
	Solution().postorder(BTTree);	//���������
	system("pause");
	return 0;
}