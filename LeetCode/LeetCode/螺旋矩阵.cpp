#include <iostream>
#include <vector>

using namespace std;

class SpiralMatrix
{
public:
	SpiralMatrix();
	~SpiralMatrix();
	vector<vector<int> >generateMatrix(int n);
};

SpiralMatrix::SpiralMatrix()
{

}

SpiralMatrix::~SpiralMatrix()
{
}

vector<vector<int>> SpiralMatrix::generateMatrix(int n)
{
	vector<vector<int>> matrix(n, vector<int>(n));
	int k = 1, i = 0;
	while (k<=n*n)
	{
		int j = i;
		while (j < n - 1)/* 上部 */
		{
			matrix[i][j++] = k++;
		}
		j = i + 1;
		while (j<n-1)/* 上部 */
		{
			matrix[j++][n - i - 1] = k++;
		}
		j = n - i - 2;
		while (j>i)
		{
			matrix[n - i - 1][j--] = k++;
		}
		j = n - i - 1;
		while (j>i)
		{
			matrix[j--][i] = k++;
		}
	}

	return matrix;
}



int main4()
{
	SpiralMatrix spm;
	spm.generateMatrix(3);
	system("pause");
	return 0;
}