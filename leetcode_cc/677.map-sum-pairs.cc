#include <string>
#include <unordered_map>
using namespace std;

class MapSum {
    unordered_map<string, int> memo;
    unordered_map<string, int> prememo;

   public:
    MapSum() {
    }

    void insert(string key, int val) {
        int delta = val;
        if (memo.count(key)) {
            delta -= memo[key];
        }
        memo[key] = val;
        for (int i = 1; i <= key.size(); i++) {
            prememo[key.substr(0, i)] += delta;
        }
    }

    int sum(string prefix) {
        return prememo[prefix];
    }
};

int main(int argc, char const* argv[]) {
    MapSum* obj = new MapSum();
    obj->insert(key, val);
    int param_2 = obj->sum(prefix);
    return 0;
}