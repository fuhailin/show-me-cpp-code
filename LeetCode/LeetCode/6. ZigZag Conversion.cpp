#include<iostream>
#include<string>
#include<vector>
using namespace std;

//时间复杂度O(n),空间复杂度大于O(n)
string convert_V1(string s, int numRows) {
	string res="";
	if (s.length() == 0||numRows==0)
		return res;
	int lens;
	if (numRows == 1)
		return s;
	else
	{
		lens = (s.length() / (2 * numRows - 2) + 1)*(numRows - 1);
	}
	vector<vector<char>> zig(numRows, vector<char>(lens));
	bool flag = true;
	int p = 0, q = 0;
	for (int i = 0; i < s.length(); ++i)
	{
		zig[p][q] = s[i];
		if (flag)
		{
			if (p >= (numRows - 1))
			{
				flag = false;
				p--;
				q++;
			}
			else
			{
				p++;
			}
		}
		else
		{
			if (p == 0)
			{
				flag = true;
				p++;
			}
			else
			{
				p--;
				q++;
			}
		}
	}
	for (int i = 0; i < zig.size(); ++i)
	{
		for (int j = 0; j < zig[0].size(); ++j)
		{
			if (zig[i][j] != '\0')
				res = res + zig[i][j];
		}
	}
	return res;
}
 
string convert(string s, int numRows)
{
	if (numRows <= 1)
		return s;

	const int len = (int)s.length();
	string *str = new string[numRows];

	int row = 0, step = 1;
	for (int i = 0; i < len; ++i)
	{
		str[row].push_back(s[i]);

		if (row == 0)
			step = 1;
		else if (row == numRows - 1)
			step = -1;

		row += step;
	}

	s.clear();
	for (int j = 0; j < numRows; ++j)
	{
		s.append(str[j]);
	}

	delete[] str;
	return s;
}

int main()
{
	string s;
	int numRows;
	cin >> s >> numRows;
	cout << convert(s,numRows) << endl;
	system("pause");
	return 0;
}