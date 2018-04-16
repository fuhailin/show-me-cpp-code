#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

double qiuhe(int n, int m)
{
	double result = n;
	double sq = n;
	for (int i = 0; i < m-1; ++i)
	{
		sq = sqrt(sq);
		result = result + sq;
	}
	return result;
}

int main1()
{
	int n, m;
	/*%f ��Ӧ float
	%lf ��Ӧ double
	%Lf ��Ӧ long double
	%e�Կ�ѧ��������ʾ
	%g��%e��%f�������ʾ*/

	/*���Ծ�����ACM�����п��� while (~scanf("%d", &n)) {} �����Ĵ��룬��˼���ڶ��������βʱѭ��Ҳ������
	һ���ڶ�����������βʱ��scanf���ص���EOF��
	EOF����ͷ�ļ�stdio.h�ж���ĳ�����һ��Ϊ - 1��
	- 1 ��ԭ����10000001��������1111110��������11111111����ϰһ�£�������ԭ�롢���롢���붼��һ���ģ�������ԭ���Ƿ���λΪ1�������ǣ���ԭ�룩����λ���䡢����λȡ���������ǣ���ԭ�룩����λ���䡢����λȡ����ĩλ��1.
	~EOF���Ƕ�EOF���а�λȡ����������Ϊ00000000������while���������㣬ѭ��������*/
	vector<double> test;
	while (cin>>n>>m)
	{
		test.push_back(qiuhe(n, m));
	}
	for (int i = 0; i < test.size(); ++i)
	{
		printf("%.2f\n", test[i]);
		//cout << fixed << setprecision(2) << test[i] << endl;
	}
	system("pause");
	return 0;
}