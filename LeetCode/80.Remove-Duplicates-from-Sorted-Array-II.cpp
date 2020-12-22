#include<iostream>
#include<vector>
using namespace std;


int removeDuplicatesII(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int res = 1, flag = 0;
	for (int i = 1; i < nums.size(); ++i)
	{
		if (nums[i - 1] < nums[i])
		{
			flag = 0;
		}
		if (nums[i - 1] == nums[i])
		{
			flag++;
		}
		if (flag < 2)
			res++;
	}
	return res;
}

//时间复杂度O(n^2)
int removeDuplicates_V1(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int len = nums.size(), tmp;
	int res = 1;
	for (int i = 1; i<len; i++)
	{
		if (nums[i - 1] == nums[i])
		{
			for (int j = i; j < len-1; ++j)
			{
				tmp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;
			}
			--len;
			--i;
		}
		else
		{
			++res;
		}
	}
	return res;
}
//时间复杂度O(n)
int removeDuplicates(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int len = nums.size(), tmp;
	int res = 1;
	for (int i = 1; i<len; i++)
	{
		if (nums[i] != nums[i - 1])
		{
			nums[res++] = nums[i];
		}
	}
	return res;
}

int main80()
{
	int arr[] = { 0,0,1,1,1,2,2,3,3,4 };
	//通过数组a的地址初始化，注意地址是从0到5（左闭右开区间）
	vector<int> nums(begin(arr), end(arr));

	int len = removeDuplicatesII(nums);
	for (int i = 0; i < len; i++) {
		cout << (nums[i]);
	}

	//cout << removeDuplicatesII(nums);
	system("pause");
	return 0;
}