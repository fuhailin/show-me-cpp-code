#include <iostream>
#include <stack>

using namespace std;
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
    bool isSymmetric_Recursive(TreeNode *root)
    {
        return root == NULL || isSymmetricHelp(root->left, root->right);
    }

  private:
    bool isSymmetricHelp(TreeNode *left, TreeNode *right)
    {
        if (left == NULL || right == NULL)
            return left == right;
        if (left->val != right->val)
            return false;
        return isSymmetricHelp(left->left, right->right) && isSymmetricHelp(left->right, right->left);
    }

  public:
    bool isSymmetric_Nonrecursive(TreeNode *root)
    {
        if (root == NULL)
            return true;
        stack<TreeNode *> _stack;
        TreeNode *left, *right;
        if (root->left != NULL)
        {
            if (root->right == NULL)
                return false;
            _stack.push(root->left);
            _stack.push(root->right);
        }
        else if (root->right != NULL)
        {
            return false;
        }
        while (!_stack.empty())
        {
            if (_stack.size() % 2 != 0)
                return false;
            right = _stack.top();
            _stack.pop();
            left = _stack.top();
            _stack.pop();
            if (right->val != left->val)
                return false;
            if (left->left != NULL)
            {
                if (right->right == NULL)
                    return false;
                _stack.push(left->left);
                _stack.push(right->right);
            }
            else if (right->right != NULL)
            {
                return false;
            }

            if (left->right != NULL)
            {
                if (right->left == NULL)
                    return false;
                _stack.push(left->right);
                _stack.push(right->left);
            }
            else if (right->left != NULL)
            {
                return false;
            }
        }
        return true;
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}