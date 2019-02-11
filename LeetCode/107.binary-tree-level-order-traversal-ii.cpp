#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        vector<vector<int>> result;
        queue<TreeNode *> _queue;
        if (root == NULL)
            return result;
        vector<int> tmp_list;
        tmp_list.push_back(root->val);
        _queue.push(root);
        result.push_back(tmp_list);
        while (!_queue.empty())
        {
            int levelNum = _queue.size();
            tmp_list.clear();
            for (int i = 0; i < levelNum; i++)
            {
                TreeNode *tmp_root = _queue.front();
                _queue.pop();
                if (tmp_root->left != NULL)
                {
                    tmp_list.push_back(tmp_root->left->val);
                    _queue.push(tmp_root->left);
                }
                if (tmp_root->right != NULL)
                {
                    tmp_list.push_back(tmp_root->right->val);
                    _queue.push(tmp_root->right);
                }
            }
            if (!tmp_list.empty())
                result.push_back(tmp_list);
        }
        reverse(result.begin(), result.end());
        // return vector<vector<int>> (result.rbegin(), result.rend());
        return result;
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}