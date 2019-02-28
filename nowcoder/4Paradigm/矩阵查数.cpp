#include <iostream>
#include <vector>
using namespace std;
//从左下角开始遍历如果值比k小则向右走，如果值比k大则往下走
bool findk(vector<vector<int>> &matrix, int k)
{
    int m = matrix.size();
    int n = matrix[0].size();
    m--;
    int i = 0;
    while (m >= 0 && i < n)
    {
        if (matrix[m][i] == k)
        {
            return true;
        }
        else if (matrix[m][i] > k)
            m--;
        else
            i++;
    }
    return false;
}

int main()
{
    int m, n; // 输入两个整数m,n, 且 0<m<=3000, 0<n<=3000.
    cin >> m >> n;
    if (m == 0 || n == 0)
    {
        cout << "false" << endl;
        return 0;
    }
    //接着输入一个vector<vector<int>> matrix矩阵，大小为m行n列
    vector<vector<int>> vec(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> vec[i][j];
    int k; //与一个int k，为需要查找的数字。
    cin >> k;
    bool res = findk(vec, k);
    //输出true或者false，true表示该数k存在于该matrix矩阵中，false表示该数k不存在于该matrix矩阵中。
    cout << boolalpha << res << endl;
    return 0;
}
