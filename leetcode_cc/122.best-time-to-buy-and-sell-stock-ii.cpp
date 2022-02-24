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
            minprice = prices[i];
        if ((prices[i] - minprice) > maxprofit)
        {
            maxprofit = prices[i] - minprice;
        }
    }
    return maxprofit;
}

int main(int argc, char const *argv[])
{
    vector<int> test{7, 6, 4, 3, 1};
    // int res = maxProfit(test);
    int res = 0x80000000;
    cout << res << endl;
    return 0;
}
