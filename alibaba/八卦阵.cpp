#include "stdlib.h"
#include <iostream>
#include<vector>
#include <iomanip>
#include<set> 
using namespace std;

struct node
{
	int flag = 0;
	int value;
};

int getMilitary(vector<vector<node>> matrix, int x, int y)
{
	int military = 0;
	int row = matrix.size();
	int col = matrix[0].size();
	if (x >= 0 && y >= 0 && x < row&&y < col&&matrix[x][y].flag == 0)
	{
		military = military + matrix[x][y].value;
		matrix[x][y].flag = 1;
		return military + getMilitary(matrix, x - 1, y) + getMilitary(matrix, x + 1, y) + getMilitary(matrix, x, y - 1) + getMilitary(matrix, x, y + 1) +
			getMilitary(matrix, x - 1, y - 1) + getMilitary(matrix, x - 1, y + 1) + getMilitary(matrix, x + 1, y - 1) + getMilitary(matrix, x + 1, y + 1);
	}
	return military;
}

int main()
{
	int m, n;
	//cout << "请输入行和列：";
	cin >> m >> n;

	//注意下面这一行：vector <int后两个 "> "之间要有空格！否则会被认为是重载 "> > "。   
	vector<vector<node> > p(m, vector<node>(n));

	//cout << "请输入数据：";
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> p[i][j].value;

	int Big = 0;
	int Small = 0x7fffffff;

	//cout << "输出数据：" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (p[i][j].flag==0)
			{
				int temp = getMilitary(p, i, j);
				if (temp > Big)
					Big = temp;
				if (temp < Small)
					Small = temp;
			}
		}
	}
	cout << Big << endl << Small;
	system("pause");
	return 0;
}