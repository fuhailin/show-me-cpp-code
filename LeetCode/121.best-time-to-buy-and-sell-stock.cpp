#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int maxprofit = 0;
    for (int i = 0; i < prices.size(); i++)
    {
        if (prices[i] > prices[i - 1])
        {
            maxprofit = maxprofit + prices[i] - prices[i - 1];
        }
    }
    return maxprofit;
}

int main()
{
    vector<int> test{7, 1, 5, 3, 6, 4};
    cout << maxProfit(test) << endl;
}