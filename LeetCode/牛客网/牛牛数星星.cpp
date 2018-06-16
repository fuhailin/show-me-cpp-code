#include<iostream>
#include<vector>
using namespace std;

int countStar(vector<vector<int>> stars,vector<int> ques)
{
	int res = 0;
	int a1 = ques[0], b1 = ques[1], a2 = ques[2], b2 = ques[3];
	for (int i = 0; i < stars.size(); i++)
	{
		if (stars[i][0] >= a1 && stars[i][0] <= a2 && stars[i][1] >= b1 && stars[i][1] <= b2)
			res++;
	}
	return res;
}

int main()
{
	int n,m;
	cin >> n;
	vector<vector<int>> stars(n, vector<int>(2));
	for (int i = 0; i < n; i++)
	{
		cin >> stars[i][0] >> stars[i][1];
	}
	cin >> m;
	vector<vector<int>> ques(m, vector<int>(4));
	for (int i = 0; i < m; i++)
	{
		cin >> ques[i][0] >> ques[i][1] >> ques[i][2] >> ques[i][3];
	}

	for (int i = 0; i < m; i++)
	{
		cout << countStar(stars, ques[i]) << endl;
	}

	system("pause");
	return 0;
}