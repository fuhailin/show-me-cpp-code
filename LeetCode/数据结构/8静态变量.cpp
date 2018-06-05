#include<iostream>
#include <vector>
using namespace std;

#define MAX 100
int X = 100000;
int f[MAX][MAX];

int getmax(int a, int b) {
	return a>b ? a : b;
}


int suanfa(vector<int> tmp,int m) {//�����ܳ���Ϊn�����еĻ���Ϊm�������к�͵����ֵ����Сֵ
	int i, j, k, temp, min;
	f[0][1] = 0;
	for (i = 1; i <= tmp.size(); i++)  //f[i][1]ǰi�����ݷֳ�һ�ε������Сֵ��
		f[i][1] = f[i - 1][1] + tmp[i];//ǰi-1��+��ǰ=ǰi��

	for (i = 2; i <= tmp.size(); i++) {
		for (j = 2; j <= m; j++) {
			for (k = 1, temp = X; k<i; k++) {
				min = getmax(f[i][1] - f[k][1], f[k][j - 1]);//�Ƚϵõ����
				if (min<temp)
					temp = min;
			}
			f[i][j] = temp;
		}
	}
	return f[tmp.size()][m];
}



int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	vector<int> tmp(n);
	for (int i = 0; i < n; i++)
	{
		cin >> tmp[i];
	}
	suanfa(tmp, m);
	system("pause");
	return 0;
}