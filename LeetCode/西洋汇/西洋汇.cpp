// 西洋汇.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int find(int a, int b, int c)
{
	if (b <= 0)
		return find(-1 * b, -1 * a, c);
	else
	{
		if (a < 0)
			return find(0, b, c) + find(1, -1 * a, c);
		else
		{
			int result = 0;
			if (a == 0 || (a%c == 0 && b%c == 0))
				result++;
			if (c > b)
				return result;
			int tmp1 = a / c;
			int tmp2 = b / c;
			result += tmp2 - tmp1;
			return result;
		}
	}
}

int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	cout << find(a, b, c);
	system("pause");
    return 0;
}

