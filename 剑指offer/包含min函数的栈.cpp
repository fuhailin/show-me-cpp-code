#include <iostream>
#include <stack>

using namespace std;
stack<int> stack1, stack2;

void push(int value)
{
        stack1.push(value);
        if (stack2.empty())
        {
                stack2.push(value);
        }

        else if (value < stack2.top())
        {
                stack2.push(value);
        }
        else
        {
                stack2.push(stack2.top());
        }
}

void pop()
{
        stack1.pop();
        stack2.pop();
}

int top()
{
        return stack1.top();
}

int min()
{
        return stack2.top();
}

int main()
{
        return 0;
}