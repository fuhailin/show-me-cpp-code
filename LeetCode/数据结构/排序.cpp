#include <iostream>;
using namespace std;

/*  ÷±Ω”≤Â»Î≈≈–Ú  */
void InsertSort(int R[], int n)
{
	int temp;
	for (int i = 1; i < n; ++i)
	{
		temp = R[i];
		for (int j = i; j >= 0; --j)
		{
			while (j>=0&&temp<R[j-1])
			{
				R[j] = R[j - 1];
				--j;
			}
			R[j] = temp;
		}
	}
}

/*  ’€∞Î≤Â»Î≈≈–Ú  */
void HalfInsertSort(int R[], int n)
{
	int i, j, head, rear, mid, tmp;
	for (i = 1; i < n; ++i)
	{
		tmp = R[i];
		head = 0;
		rear = i;
		while (rear > head)
		{
			mid = (head + rear) / 2;
			if (tmp > R[mid])
			{
				head = mid + 1;
			}
			else
			{
				rear = mid - 1;
			}
		}
		for (j = i-1; j >= rear+1; --j)
		{
			R[j] = R[j - 1];
		}
		R[j+1] = tmp;
	}
}

/*  √∞≈›≈≈–Ú  */
void BubbleSort(int R[], int n) 
{
	int temp;
	for (int i = n - 1; i >= 1; --i)
	{
		//flag = 1;
		for (int j = i; j >= 0; --j)
		{
			if (R[j-1] > R[j])
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

void QuickSort(int R[], int left, int right)
{
	int temp;
	int i = left, j = right;
	if (left < right)
	{
		temp = R[left];
		while (i!=j)
		{
			while (j>i&&R[j]>temp)
			{
				--j;
			}
			if (i < j)
			{
				R[i] = R[j];
				++i;
			}
			while (i<j&&R[i]<temp)
			{
				++i;
			}
			if (i < j)
			{
				R[j] = R[i];
				--j;
			}
		}
		R[i] = temp;
		QuickSort(R, left, i - 1);
		QuickSort(R, i + 1, right);
	}
}

int main()
{
	int test[10] = { 9,8,7,6,5,4,3,2,1,0 };
	InsertSort(test,10);
	QuickSort(test, 0, 9);
	HalfInsertSort(test, 10);
	//BubbleSort(test, 10);
	int n = 10;
	int temp;
	for (int i = 0; i < n; ++i)
	{
		//flag = 1;
		for (int j = i; j >= 0; --j)
		{
			if (test[j - 1] > test[j])
			{
				temp = test[j - 1];
				test[j - 1] = test[j];
				test[j] = temp;
				//flag = 0;
			}
			/*if (flag)
			break;*/
		}
	}

	for (int i = 0; i<10; i++)
		cout << test[i] << " ";
	getchar();
	return 0;
}