// LeetCode.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <algorithm> 
using namespace std;

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty()) return 0;
		int pre = 0, cur = 0, n = nums.size();
		while (cur < n) {
			if (nums[pre] == nums[cur]) 
				++cur;
			else 
				nums[++pre] = nums[cur++];
		}
		return pre + 1;
	}
	/*int removeElement(vector<int>& nums, int val) {
		if (nums.empty()) return 0;
		int p = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val)
			{
				nums[p] = nums[i];
				p++;
			}
		}
		return p;
	}*/
	int removeElement(vector<int>& nums, int val) {
		if (nums.empty()) return 0;
		int p, q;
		p = q = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[q] != val)
			{
				nums[p++] = nums[q++];
			}
			else
			{
				q++;
			}
		}
		return p;
	}
	/*爬楼梯--递归*/
	int climbStairs(int n) 
	{
		if (n == 1) {
			return 1;
		}
		if (n == 2) {
			return 2;
		}
		return climbStairs(n - 1) + climbStairs(n - 2);
	}
	/*爬楼梯--迭代*/
	int climbStairs1(int n)
	{
		int steps[999];
		steps[0] = 0;
		steps[1] = 1;
		steps[2] = 2;
		if (n == 1) return steps[1];
		if (n == 2) return steps[2];
		else
		{
			for (int i = 3; i < 999; i++)
			{
				steps[i] = steps[i - 1] + steps[i - 2];
			}
		}
		return steps[n];
	}

	/*爬楼梯--通项公式*/
	int climbStairs2(int n)
	{
		n++;
		double root5 = sqrt(5);
		//double root5 = pow(5, 0.5);
		double result = 1 / root5*(pow((1 + root5) / 2, n) - pow((1 - root5) / 2, n));
		return (int)(result);
	}
	/*使用最小花费爬楼梯*/
	int minCostClimbingStairs(vector<int>& cost) {
		int n = cost.size();
		vector<int> cm(n + 1); //Top means above the last stair

							   //Edge Case
		if (n<2) return 0;

		//Can either start from index 0 or 1
		cm[0] = 0;
		cm[1] = 0;

		//DP to find the minimum cost to reach the last stair or second last stair
		for (int i = 2; i <= n; i++)
			cm[i] = min(cm[i - 2] + cost[i - 2], cm[i - 1] + cost[i - 1]);

		//Cost to reach the stair above the last
		return cm[n];
	}
};

int main2()
{
	vector<int> tmp(10);
	tmp[0] = 1; tmp[1] = 100; tmp[2] = 1; tmp[3] = 1; tmp[4] = 1;
	tmp[5] = 100; tmp[6] = 1; tmp[7] = 1; tmp[8] = 100; tmp[9] = 1;
	//int n = sizeof(tmp) / sizeof(tmp[0]);

	Solution solu;
	int test = solu.removeElement(tmp,100);
	cout << test<<endl;
	//getchar();
	system("pause");
	return 0;
}

