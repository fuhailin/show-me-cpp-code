#include <iostream>
#include <vector>
using namespace std;

int Gcd(int a, int b)
{
	while (b != 0)
	{
		int r = b;
		b = a % b;
		a = r;
	}
	return a;
}

vector<int> gerA(int N, int p)
{
	vector<int> A(N+1);
	A[0] = 0;
	A[1] = p;
	for (int i = 2; i <= N; ++i)
	{
		A[i] = (A[i - 1] + 153) % 10;
	}
	return A;
}

int main()
{
	int N, n, m, p;
	cin >> N >> n >> m >> p;
	vector<int> temp = gerA(N, p);
	int res = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			res = res + temp[Gcd(i, j)];
		}
	}
	cout << res;
	system("pause");
	return 0;
}