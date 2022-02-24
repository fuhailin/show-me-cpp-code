#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		int rows = array.size();
		int cols = array[0].size();
		
		for (int i = 0; i < cols; i++)
		{
			int row_low = 0, row_hogh = rows - 1, row_mid = (row_low + row_hogh) / 2;
			while (row_hogh >= row_low)
			{
				if (array[row_mid][i] == target)
					return true;
				if (array[row_mid][i] > target)
				{
					row_hogh = row_mid-1;
					row_mid = (row_low + row_hogh) / 2;
				}
				else
				{
					row_low = row_mid+1;
					row_mid = (row_low + row_hogh) / 2;
				}
			}
		}
		return false;
	}


	void printMatrix(vector<vector<int> > array)
	{
		for (int i = 0; i < array.size(); i++)
		{
			for (int j = 0; j < array[0].size(); j++)
			{
				cout << array[i][j] << "\t";
			}
			cout << endl;
		}
	}
};
int main1()
{
	vector<vector<int> > array(7, vector<int>(8));
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < array[0].size(); j++)
		{
			array[i][j] = (i + 1)*(j + 1);
		}
	}
	Solution().printMatrix(array);
	bool start = Solution().Find(9, array);
	cout << boolalpha;	//print true not 1
	cout << start;
	system("pause");
	return 0;
}