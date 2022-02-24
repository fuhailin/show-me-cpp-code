#include <iostream>
#include <vector>
using namespace std;

int minNumberInRotateArray(vector<int> rotateArray)
{
	int length = rotateArray.size();
	if (length <= 0)
		throw runtime_error("Invalid parameters");
	int index1 = 0, index2 = length - 1, indexMid = index1; //indexMid初始为index1:考虑最小数字就是第一个数字的情况
	while (rotateArray[index1] >= rotateArray[index2])
	{
		if ((index2 - index1) == 1)
		{
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2) / 2;
		if (rotateArray[index1] == rotateArray[index2] && rotateArray[index1] == rotateArray[indexMid])
			return MinInOrder(rotateArray, index1, index2);
		if (rotateArray[indexMid] >= rotateArray[index1])
			index1 = indexMid;
		else if (rotateArray[indexMid] <= rotateArray[index2])
			index2 = indexMid;
	}
	return rotateArray[indexMid];
}

int MinInOrder(vector<int> numbers, int index1, int index2)
{
	int result = numbers[index1];

	for (int i = index1 + 1; i <= index2; i++)
	{
		if (numbers[i] < numbers[index1])
			result = numbers[i];
	}
	return result;
}

int main()
{
	vector<int> numbers;
	while (1)
	{
		int temp;
		cin >> temp;
		numbers.push_back(temp);
		char s = cin.get(); //s用来接收是否是回车
		if (s == '\n')
		{
			break;
		}
	}

	int result = minNumberInRotateArray(numbers);
	cout << result << endl;
	return 0;
}