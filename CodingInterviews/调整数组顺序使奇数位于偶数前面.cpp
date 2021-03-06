// 剑指Offer.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

///调整数组顺序使奇数位于偶数前面
void reOrderArray(vector<int> &array) {
	//int i = 0, j = array.size() - 1;
	queue<int> even, odd;
	for (int i = 0; i < array.size(); ++i)
	{
		if (array[i] % 2 == 0)
			even.push(array[i]);
		else
		{
			odd.push(array[i]);
		}
	}
	int a = 0;
	while (!odd.empty())
	{
		array[a++] = odd.front();
		odd.pop();
	}
	while (!even.empty())
	{
		array[a++] = even.front();
		even.pop();
	}
}



int main13()
{
	int a[] = { 1,2,3,4,5,6,7,8,9,0 };
	vector<int> tmp(begin(a), end(a));
	reOrderArray(tmp);
	for (int i=0; i < tmp.size(); ++i)
	{
		cout << tmp[i] << endl;
	}
	system("pause");
	return 0;
}

