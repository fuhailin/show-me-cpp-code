#include <iostream>
using namespace std;

class Sort
{
  private:
	/* partition for quick sort */
	int partition(int arr[], int left, int right)
	{
		int pivot = arr[right];
		int i = (left - 1);

		for (int j = left; j < right; j++)
		{
			if (arr[j] <= pivot)
			{
				i++;
				swap(&arr[i], &arr[j]);
			}
		}
		swap(&arr[++i], &arr[right]);
		return i;
	}
	// A utility function to swap two elements
	void swap(int *a, int *b)
	{
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}

  public:
	void QuickSort(int arr[], int left, int right)
	{
		if (left < right)
		{
			int pivot = partition(arr, left, right);
			QuickSort(arr, left, pivot - 1);
			QuickSort(arr, pivot + 1, right);
		}
	}
};

/*  直接插入排序  */
void InsertSort(int R[], int n)
{
	int temp;
	for (int i = 1; i < n; ++i)
	{
		temp = R[i];
		for (int j = i; j >= 0; --j)
		{
			while (j >= 0 && temp < R[j - 1])
			{
				R[j] = R[j - 1];
				--j;
			}
			R[j] = temp;
		}
	}
}

/*  折半插入排序  */
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
		for (j = i - 1; j >= rear + 1; --j)
		{
			R[j] = R[j - 1];
		}
		R[j + 1] = tmp;
	}
}

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

/* Function to print an array */
void printArray(int arr[], int count)
{

	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << ' ';
	}
}

int main()
{
	int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int arrSize = sizeof(arr) / sizeof(arr[0]);
	Sort sort;
	// InsertSort(test, 10);
	sort.QuickSort(arr, 0, arrSize - 1);
	// HalfInsertSort(test, 10);
	// BubbleSort(test, 10);
	printArray(arr, arrSize);
	return 0;
}