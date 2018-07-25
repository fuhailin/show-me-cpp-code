#include <iostream>
#include <cmath>
//#include<bits/stdc++.h>
//#include <bitset>
using namespace std;


string binary(int num) {

	string s = "";
	for (int a = num; a; a = a / 2)
	{
		//二进制只有两个基数，所以转换起来比较方便，若是转换为其他进制可以使用switch结构  
		s = s + (a % 2 ? '1' : '0');
	}
	//字符串反转  
	//s.begin() 获得字符串的开始位置  
	//s.end() 获得字符串的结尾位置  
	reverse(s.begin(), s.end());
	return s;
}

bool check(char *str)//判断这是不是一个回文字符串.  
{
	int i = 0;
	int j = strlen(str) - 1;
	while (i<j)
	{
		if (*(str + i) != *(str + j))
			return false;
		i++;
		j--;
	}
	return true;
}



int main()
{
	
	int n;
	cin >> n;
	int count = 0;
	for (int i = n; i >= 0; --i)
	{
		char *c;
		string temp = binary(i);
		char *p = (char*)temp.c_str();
		if (check(p))
			count++;
	}
	cout << count;
	system("pause");
	return 0;
}