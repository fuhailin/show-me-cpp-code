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

	}


private:

};

int main()
{
	printf("请输入第1个链表:\n");
	vector<int> preorder = { 1,2,4,7,3,5,6,8 };
	vector<int> midorder = { 4,7,2,1,5,3,8,6 };

	TreeNode* postorder = Solution().reConstructBinaryTree(preorder,midorder);
	system("pause");
}