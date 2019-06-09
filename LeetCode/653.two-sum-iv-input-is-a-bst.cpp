#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
/**
 * Definition for a binary tree node.
 * */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    bool findTarget(TreeNode *root, int k)
    {
        if (root == NULL)
            return false;

        vector<int> nums;
        inorder_Recursive(root, nums);
        return twoSum(nums, k);
    }

    void inorder_Recursive(TreeNode *root, vector<int> &nums)
    {
        stack<TreeNode *> s;
        TreeNode *p = root;
        while (p != NULL || !s.empty())
        {
            while (p != NULL)
            {
                s.push(p);
                p = p->left;
            }
            if (!s.empty())
            {
                p = s.top();
                nums.push_back(p->val);
                s.pop();
                p = p->right;
            }
        }
    }

    void inorder_Iteration(TreeNode *root, vector<int> &nums)
    {
        if (root != NULL)
        {
            inorder_Iteration(root->left, nums);
            nums.push_back(root->val);
            inorder_Iteration(root->right, nums);
        }
    }

    bool twoSum(vector<int> &numbers, int target)
    {
        int i = 0, j = numbers.size() - 1;
        while (i < j)
        {
            int tmp = numbers[i] + numbers[j];
            if (tmp == target)
                return true;
            else if (tmp < target)
                i++;
            else
                j--;
        }
        return false;
    }
};
int main()
{
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    bool res = Solution().findTarget(root, 4);
    cout << boolalpha << res << endl;
    return 0;
}