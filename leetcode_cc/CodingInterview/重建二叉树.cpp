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
		//创建根节点，根节点肯定是前序遍历的第一个数
		TreeNode* root = new TreeNode(pre[0]);

		//找到中序遍历根节点所在位置,存放于变量gen中
		int rootIndex = 0;

		for (int i = 0; i < vinlen; i++)
		{
			if (vin[i] == pre[0])
			{
				rootIndex = i;
				break;
			}
		}

		//对于中序遍历，根节点左边的节点位于二叉树的左边，根节点右边的节点位于二叉树的右边
		//利用上述这点，对二叉树节点进行归并
		for (int i = 0; i < rootIndex; i++)
		{
			left_vin.push_back(vin[i]);
			left_pre.push_back(pre[i + 1]);//前序第一个为根节点
		}
		for (int i = rootIndex + 1; i < vinlen; i++)
		{
			right_vin.push_back(vin[i]);
			right_pre.push_back(pre[i]);
		}

		//和shell排序的思想类似，取出前序和中序遍历根节点左边和右边的子树
		//递归，再对其进行上述所有步骤，即再区分子树的左、右子子数，直到叶节点
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
		printf("%d", node->val);// %c 输出字符型变量
	}

private:

};

int main4()
{
	printf("请输入第1个链表:\n");
	vector<int> preorder = { 1,2,4,7,3,5,6,8 };
	vector<int> midorder = { 4,7,2,1,5,3,8,6 };

	TreeNode* BTTree = Solution().reConstructBinaryTree(preorder,midorder);
	Solution().postorder(BTTree);	//后序遍历：
	system("pause");
	return 0;
}