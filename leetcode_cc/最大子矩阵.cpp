#include <iostream>
#include <vector>
using namespace std;

int getMax(vector<vector<int>> matrix)
{
    
    return 0;
}

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> matrix(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
        }
    }
    int res = getMax(matrix);
    cout << res << endl;

    return 0;
}