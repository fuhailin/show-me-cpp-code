#include <iostream>  
#include <string.h>  
using namespace std;

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

int get_str(char *str)
{
	int result=0;
	int n = strlen(str) - 1;

	char *p = new char[n + 1];
	strcpy(p, str);
	int i = 0;
	int j;
	for (; i<n; i++)
	{
		p += i;
		j = n - i;
		while (j>=0)//这里j不用等于0，一个字符虽然也是回文字符，但是没有必要，我们这里求的回文是>=2的字符串。  
		{
			*(p + j + 1) = '\0';
			if (check(p))
			{
				result++;
				cout << p << "   ";
				cout << endl;
			}
			j--;
		}
		strcpy(p, str);
	}
	return result;
}
//思想是i=0开始，j=n开始  
//i不变，j--，知道i>=j时才把以i=0这个位置的所有字符串找寻了一遍，  
//i++，j=n开始重复上述操作.  
//.....  
//知道i==n时，结束，并输出求得的所有回文字符串.  

int main9()
{
	char s[] = "ABA";
	int test2=get_str(s);
	system("pause");
	return 0;
}