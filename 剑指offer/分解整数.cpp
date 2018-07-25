#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#define maxn 100009
int fact[maxn];
bool prime[maxn];
ll mod = 987654321;
int cal(int t, int p) {
	int cnt = 0;
	while (t % p == 0) {
		cnt++;
		t /= p;
	}
	return cnt;
}
void first() {
	memset(prime, true, sizeof(prime));
	prime[1] = false;
	for (int i = 2; i <= 100000; i++) {
		int top = sqrt(i);
		for (int j = 2; j <= top; j++) {
			if (i % j == 0) {
				prime[i] = false;
				break;
			}
		}
	}
}
void solve(int Limit) {
	first();
	for (int i = 2; i <= Limit; i++) {
		int top = sqrt(i);
		for (int j = 2; j <= top; j++) {
			if (prime[j] && i % j == 0) {
				fact[j] = max(fact[j], cal(i, j));
			}
		}
		if (prime[i])
			fact[i] = max(fact[i], 1);
	}
}
int main() {
	ll n;
	cin >> n;
	solve(n);
	ll ans = 1;
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= fact[i]; j++) {
			ans = ans * i % mod;
		}
	}
	cout << ans << endl;
	system("pause");
	return 0;
}


