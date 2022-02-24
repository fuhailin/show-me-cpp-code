class Solution {
    vector<int> path;
    unordered_set<int> res;
    void backtracking(vector<int>& digits, vector<bool> &used) {
        if(path.size() == 3) {
            int num = path[0]*100 + path[1]*10 + path[2];
            res.insert(num);
            return;
        }
        for(int i = 0; i < digits.size(); i++) {
            if(used[i] || path.empty() && digits[i]==0 || path.size()==2 && digits[i]%2==1) continue;
            used[i] = true;
            path.push_back(digits[i]);
            backtracking(digits, used);
            path.pop_back();
            used[i] = false;
        }

    }
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<bool> used(digits.size(), false);
        sort(digits.begin(), digits.end());
        backtracking(digits, used);
        vector<int> result(res.begin(), res.end());
        sort(result.begin(), result.end());
        return result;
    }
};