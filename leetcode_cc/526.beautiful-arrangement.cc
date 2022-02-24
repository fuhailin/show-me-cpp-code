#include <vector>
using namespace std;

class Solution {
    bool check(){
        
    }

    void backtracking(const int &n, vector<vector<int>> &arrs){
        if(n==0){
            return;
        }
        

    }
public:
    int countArrangement(int n) {
        vector<vector<int>> arrs;
        backtracking(n, arrs);
        return arrs.size();
    }
};