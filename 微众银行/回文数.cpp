#include <iostream>
#include <cmath>
//#include<bits/stdc++.h>
//#include <bitset>
using namespace std;


string binary(int num) {

	string s = "";
	for (int a = num; a; a = a / 2)
	{
		//������ֻ����������������ת�������ȽϷ��㣬����ת��Ϊ�������ƿ���ʹ��switch�ṹ  
		s = s + (a % 2 ? '1' : '0');
	}
	//�ַ�����ת  
	//s.begin() ����ַ����Ŀ�ʼλ��  
	//s.end() ����ַ����Ľ�βλ��  
	reverse(s.begin(), s.end());
	return s;
}

bool check(char *str)//�ж����ǲ���һ�������ַ���.  
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