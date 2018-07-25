#include <iostream>
using namespace std;

/*  冒泡排序  */
void BubbleSort(int R[], int n)
{
	int temp;
	for (int i = n - 1; i >= 1; --i)
	{
		//flag = 1;
		for (int j = i; j >= 0; --j)
		{
			if (R[j - 1] > R[j])
			{
				temp = R[j - 1];
				R[j - 1] = R[j];
				R[j] = temp;
				//flag = 0;
			}
			/*if (flag)
			break;*/
		}
	}
}

/*  直接插入排序  */
void InsertSort(int R[], int n)
{
	int temp;
	for (int i = 1; i < n; ++i)
	{
		temp = R[i];
		for (int j = i; j >= 0; --j)
		{
			while (j >= 0 && temp<R[j - 1])
			{
				R[j] = R[j - 1];
				--j;
			}
			R[j] = temp;
		}
	}
}

int function(int a, int b, int c)
{
	int temp[3];
	temp[0] = a; temp[1] = b; temp[2] = c;
	InsertSort(temp, 3);

	int res = 0;
	if (temp[0] == temp[1]&&temp[1] == temp[2])
		return ++res;
	if (temp[0] == temp[1] || temp[1] == temp[2])
	{
		if (temp[2] - temp[0] > 1)
		{
			temp[0] = temp[0] + 2;
			++res;
			return res + function(temp[0], temp[1], temp[2]);
		}
		else
		{
			temp[0] = temp[0] + 1;
			temp[1] = temp[1] + 1;
			++res;
			return res + function(temp[0], temp[1], temp[2]);
		}
	}
	if (temp[2] - temp[0] > 1)
	{
		temp[0] = temp[0] + 2;
		++res;
		return res + function(temp[0], temp[1], temp[2]);
	}
	else
	{
		temp[0] = temp[0] + 1;
		temp[1] = temp[1] + 1;
		++res;
		return res + function(temp[0], temp[1], temp[2]);
	}

}
int main() {
	int a, b,c;
	while (cin >> a >> b >> c)//注意while处理多个case
	{
		cout<< function(a, b, c);
	}
}