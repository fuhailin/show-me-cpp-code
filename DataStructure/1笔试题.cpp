// ������.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include <iostream>
#include<vector>
#include <iomanip>
using namespace std;


int main1()
{
	int m, n;
	//cout << "�������к��У�";
	cin >> m >> n;

	//ע��������һ�У�vector <int������ "> "֮��Ҫ�пո񣡷���ᱻ��Ϊ������ "> > "��   
	vector<vector<int> > p(m, vector<int>(n));

	//cout << "���������ݣ�";
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> p[i][j];

	//cout << "������ݣ�" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(3) << p[i][j];
		cout << endl;
	}
	system("pause");
    return 0;
}

