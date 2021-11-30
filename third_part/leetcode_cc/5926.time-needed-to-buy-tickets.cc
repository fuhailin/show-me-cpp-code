#include "bits/stdc++.h"

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int res = 0;

        for(int i = 0; i < tickets.size(); i++) {
            if(i <= k) {
                if(tickets[i] <= tickets[k] ) {
                    res += tickets[i];
                } else {
                    res += tickets[k];
                }
            } else {
                if(tickets[i] < tickets[k] ) {
                    res += tickets[i];
                } else {
                    res += tickets[k] - 1;
                }
            }
        }
        return res;
    }
};


int main(int argc, char const *argv[])
{
    Solution so;
    vector<int> test = {5,1,1,1};
    int res = so.timeRequiredToBuy(test, 0);
    cout << "res: " << res << endl;
    return 0;
}
