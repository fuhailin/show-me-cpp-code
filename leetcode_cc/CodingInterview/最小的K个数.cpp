#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int mball_nfloor(int m, int n) {
	if (m <= 0 || n <= 0)
		return 0;
	vector<vector<int>> result(m+1, vector<int>(n+1));
	int temp_min = n + 1;
	int temp_max = 0;
	//for n==0 and n==1
	for (int i = 0;i <= m;i++) {
		result[i][0] = 0;
		result[i][1] = 1;
	}
	//for m==0 and m==1
	for (int i = 0;i <= n;i++) {
		result[1][i] = i;
		result[0][i] = 0;
	}
	if (m > 1 && n > 1) {
		//start from 2 balls
		for (int a = 2;a <= m;a++) {
			//start from 1 floors
			for (int i = 1;i <= n;i++) {
				for (int k = 1;k <= i;k++) {
					temp_max = max(result[a - 1][k - 1] + 1, result[a][i - k] + 1);
					temp_min = min(temp_min, temp_max);
				}
				result[a][i] = temp_min;
				temp_min = n + 1;
			}
		}
	}
	return result[m][n];
}


int main(int argc, char const *argv[])
{
	int x, y;
	cin >> x >> y;
	int res = mball_nfloor(x, y);
	cout  << res << endl;
	return 0;
}