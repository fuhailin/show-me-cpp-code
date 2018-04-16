#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		/*if (rotateArray.size() == 0)
			return 0;*/

	}
	/*二进制中1的个数*/
	int  NumberOf1(int n) {
		int count = 0;
		unsigned int flag = 1;
		while (flag)
		{
			if (n&flag)
			{
				count++;
			}
			flag = flag << 1;
		}
		return count;
	}

};


int main6()
{
	Solution solu;
	int result=solu.NumberOf1(-7);
	cout << result << endl;
	system("pause");
	return 0;
}