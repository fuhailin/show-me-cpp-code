#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int minprice = 0x7fffffff;
    int maxprofit = 0;
    for (int i = 0; i < prices.size(); i++)
    {
        if (prices[i] < minprice)
        {
            minprice = prices[i];
        }
        else
        {
            if ((prices[i] - minprice) > maxprofit)
                maxprofit = prices[i] - minprice;
        }
    }
    return maxprofit;
}

int main()
{
    vector<int> test{7, 1, 5, 3, 6, 4};
    cout << maxProfit(test) << endl;
}