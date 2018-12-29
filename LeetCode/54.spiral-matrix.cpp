/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /
=============================================================================*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
   vector<int> result;
   if (matrix.size() == 0)
      return result;
   int row = matrix.size();
   int col = matrix[0].size();
   int circle = (min(row, col) + 1) >> 1;
   for (int i = 0; i < circle; i++)
   {
      //from left to right
      for (int a = i; a < col - i; a++)
         result.push_back(matrix[i][a]);
      //from up to dowm
      for (int b = i + 1; b < row - i; b++)
         result.push_back(matrix[b][col - i - 1]);
      //from right to left 终止列号>起始列号 && (终止行号) > 起始行号
      for (int c = col - i - 2; (c >= i) && (row - i - 1 > i); c--) // 至少两行两列
         result.push_back(matrix[row - i - 1][c]);
      //from bottom to top 终止行号>起始行号+1&& 终止列号 > 起始列号
      for (int d = row - i - 2; (d > i) && (col - i - 1 > i); d--) // 至少三行两列
         result.push_back(matrix[d][i]);
   }
   return result;
}
int main()
{
   int M, N;
   cout << "The rows and columns of matrix" << endl;
   cin >> M >> N;

   vector<vector<int>> matrix(M, vector<int>(N));
   vector<int> res;
   /* input example
3 4
1 2 3 4
5 6 7 8
9 10 11 12
*/
   for (int i = 0; i < M; i++)
   {
      for (int j = 0; j < N; j++)
      {
         cin >> matrix[i][j];
      }
   }
   res = printMatrix(matrix);
   for (int i = 0; i < res.size(); i++)
   {
      cout << res[i] << " ";
   }

   return 0;
}