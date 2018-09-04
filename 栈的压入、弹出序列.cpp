#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool isPopOrder(vector<int> pushV, vector[int] popV)
{
    if ((popV.size() == 0) || popV.size() != pushV.size())
        return false;
    stack<int> test;
    for (int i = 0, j = 0; i < pushV.siez();i++)
    {
        test.push(pushV[i]);
        while (!test.empty() && test.top() == popV[j])
	{
            test.pop();
            j++;
	}
    }
    return test.empty();
}

int main()
{
    int[] pushV = [ 1, 2, 3, 4, 5 ];
    int[] popV = [ 4, 3, 5, 1, 2 ];
    bool tmp = isPopOrder(pushV, popV);
    cout << tmp << endl;
    return 0;
}
