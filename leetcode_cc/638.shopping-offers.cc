#include <map>
#include <vector>
using namespace std;

class Solution {
   public:
    // 不同的needs所需的价格
    map<vector<int>, int> _cache;

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int n = price.size();
        // 过滤不需要计算的大礼包，只保留需要计算的大礼包
        vector<vector<int>> filterSpecial;
        for (auto& sp : special) {
            int totalCount = 0, totalPrice = 0;
            for (int i = 0; i < n; ++i) {
                totalCount += sp[i];
                totalPrice += sp[i] * price[i];
            }
            if (totalCount > 0 && totalPrice > sp[n]) {
                filterSpecial.emplace_back(sp);
            }
        }

        return dfs(needs, price, special);
    }

    int dfs(vector<int> needs, vector<int>& price, vector<vector<int>>& special) {
        // 如果子问题已经计算过 直接返回
        if (_cache[needs]) {
            return _cache[needs];
        }
        int ans = 0;
        // 最弱的方式；不购买大礼包
        for (int i = 0; i < needs.size(); i++) {
            ans += needs[i] * price[i];
        }

        // 遍历每个礼包，购买它，看看是不是能获得更便宜的价格
        for (int i = 0; i < special.size(); i++) {
            vector<int> next = needs;
            bool valid = true;
            // 因为购买的数量需要正好是needs 所以大礼包的某个商品不能超过needs的商品数量
            for (int item = 0; item < price.size(); item++) {
                if (special[i][item] > needs[item]) {
                    valid = false;
                    break;
                }
            }

            // 当前大礼包不符合要求 跳过
            if (!valid) continue;
            // 当前大礼包符合要求，用next数组记录买过大礼包之后还需要买多少商品
            for (int item = 0; item < price.size(); item++) {
                next[item] -= special[i][item];
            }

            // 在整个遍历过程中，我们要找价格最小的一种方式
            ans = min(ans, dfs(next, price, special) + special[i].back());
        }

        // 更新cache
        _cache[needs] = ans;
        return ans;
    }
};
