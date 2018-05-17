#include <iostream>
#include <vector>
using namespace std;

#define bai (num/100)  
#define shi  ((num-bai*100)/10)  
#define ge  (num%10)  

void shuixianflower(int m,int n)
{
	if (m >= 100 && m <= n&&n <= 999)
	{
		int flag = 0;
		for (int num = m; num <= n; num++)
			if (num == bai*bai*bai + shi*shi*shi + ge*ge*ge)
			{
				if (flag == 0)
				{
					printf("%d", num);
				}
				else
				{
					printf(" %d", num);
				}
				flag++;
			}
		if (flag == 0)
			cout << "no";
	}
}

int main2()
{
	vector<vector<int>> test1;
	vector<int> test2(2);
	int m, n;
	while (cin>>m>>n)
	{
		test2[0] = m;
		test2[1] = n;
		test1.push_back(test2);
	}
	for (int i = 0; i < test1.size(); ++i)
	{
		shuixianflower(test1[i][0], test1[i][1]);
		cout << endl;
	}
	system("pause");
	return 0;
}