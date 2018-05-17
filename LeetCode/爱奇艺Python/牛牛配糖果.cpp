#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main3() {
	//freopen("1.in","r",stdin);
	int n, m ;
	cin >> n >> m;
	vector<vector<int> > p(n, vector<int>(2));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &p[i][j]);
		}
	}

	//for()

	system("pause");
	return 0;
}