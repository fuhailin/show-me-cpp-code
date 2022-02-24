#include <iostream>
#include <stack>
using namespace std;
class Solution
{
public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		if (stack1.empty() && stack2.empty())
			return NULL;
		if (stack2.empty())
		{
			while (!stack1.empty())
			{
				stack2.push(stack1.top());
				stack1.pop();
			}
			int restult=stack2.top();
			stack2.pop();
			return restult;
		}
		else
		{
			int restult = stack2.top();
			stack2.pop();
			return restult;
		}
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};


int main5()
{
	Solution solu;
	solu.push(1);
	return 0;
}