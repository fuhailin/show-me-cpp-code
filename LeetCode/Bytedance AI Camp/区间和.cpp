/*
区间和最大同时区间0个数小于等于3
*/
#include <iostream>
#include<vector>
using namespace std;

int getBlock(vector<int> num)
{
	if (num.size() == 0)
		return 0;
	int res = 0;
	int flag = 0;
	int tmp = num[0], tmp_index = 0;
	for (int i = 0; i < num.size(); i++)
	{
		if (num[i] > tmp)
		{
			tmp = num[i];
			tmp_index = i;
		}
	}
	res = num[tmp_index];
	int left = tmp_index;
	while ((left - 1) >= 0 && flag < 3)
	{
		if (num[--left] == 0)
			flag++;
		res = res + num[left];
	}
	int right = tmp_index;
	while (((right+1)<num.size())&&flag<3)
	{
		if (num[++right] == 0)
			flag++;
		res = res + num[right];
	}
	vector<int>::const_iterator begin = num.begin();
	vector<int>::const_iterator last = num.begin() + left;
	vector<int> new_arr(begin, last);
	int left_max = getBlock(new_arr);

	begin = num.begin() + right + 1;
	last = num.end();
	vector<int> new_arr1(begin, last);
	int right_max = getBlock(new_arr1);

	if (left_max > res)
		res = left_max;
	if (right_max > res)
		res = right_max;
	return res;
}
int main() {
	int n;
	cin >> n;
	vector<int> array(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> array[i];
	}
	cout << getBlock(array) << endl;
	system("pause");
	return 0;
}