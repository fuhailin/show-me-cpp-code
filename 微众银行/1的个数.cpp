#include <iostream>
#include <cmath>
using namespace std;
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
int main3()
{
	int a, b, c, temp;
	cin >> a >> b >> c;
	temp = pow(2, a) + pow(2, b) - pow(2, c);
	cout << NumberOf1(temp);
	return 0;
}