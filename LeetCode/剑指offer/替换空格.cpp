#include <iostream>
using namespace std;
class Solution
{
public:
	/* ��Ŀ����:
	��ʵ��һ����������һ���ַ����еĿո��滻�ɡ�%20�������磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy��
	lengthΪ�ַ�����string��������*/
	void replaceSpace(char *str, int length) {
		if (str == NULL&&length<=0)
			return;
		int CountOfBlanks = 0;
		int Originallength = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			Originallength++;
			if (str[i] == ' ')
				++CountOfBlanks;
		}
		int len = Originallength + 2 * CountOfBlanks;
		if (len >length)
			return;

		char*pStr1 = str + Originallength;//���ƽ�������\0��
		char*pStr2 = str + len;
		while (pStr1<pStr2&&*pStr1>=0)
		{
			if (*pStr1 == ' ')
			{
				*pStr2-- = '0';
				*pStr2-- = '2';
				*pStr2-- = '%';
			}
			else
			{
				*pStr2-- = *pStr1;
			}
			--pStr1;
		}
	}

};
int main2()
{
	

	char str[10] = "a b c";

	Solution().replaceSpace(str, 10);
	cout << str << endl;
	system("pause");
 	return 0;
}
