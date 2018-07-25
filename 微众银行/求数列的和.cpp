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
	/*%f 对应 float
	%lf 对应 double
	%Lf 对应 long double
	%e以科学计数法显示
	%g在%e和%f中择短显示*/

	/*可以经常在ACM代码中看到 while (~scanf("%d", &n)) {} 这样的代码，意思是在读到输入结尾时循环也结束。
	一般在读到输入流结尾时，scanf返回的是EOF。
	EOF是在头文件stdio.h中定义的常量，一般为 - 1。
	- 1 的原码是10000001，反码是1111110，补码是11111111。复习一下，正数的原码、反码、补码都是一样的；负数的原码是符号位为1，反码是（对原码）符号位不变、其余位取反，补码是（对原码）符号位不变、其余位取反、末位加1.
	~EOF则是对EOF进行按位取反操作，则为00000000。所以while条件不满足，循环结束。*/
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