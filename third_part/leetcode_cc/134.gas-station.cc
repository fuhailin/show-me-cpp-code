#include <numeric>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
    {
        int totalGas = accumulate(gas.begin(), gas.end(), 0);
        int totalCost = accumulate(cost.begin(), cost.end(), 0);
        if(totalGas < totalCost) return -1;

        int currentGas = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); i++) {
            currentGas += gas[i] - cost[i];
            if(currentGas < 0) {
                currentGas = 0;
                start = i + 1;
            }
        }
        return start;
    }
};