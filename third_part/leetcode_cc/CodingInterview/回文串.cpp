#include <iostream>  
#include <string.h>  
using namespace std;

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
		while (j>=0)//����j���õ���0��һ���ַ���ȻҲ�ǻ����ַ�������û�б�Ҫ������������Ļ�����>=2���ַ�����  
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
//˼����i=0��ʼ��j=n��ʼ  
//i���䣬j--��֪��i>=jʱ�Ű���i=0���λ�õ������ַ�����Ѱ��һ�飬  
//i++��j=n��ʼ�ظ���������.  
//.....  
//֪��i==nʱ���������������õ����л����ַ���.  

int main9()
{
	char s[] = "ABA";
	int test2=get_str(s);
	system("pause");
	return 0;
}