#include <iostream>
using namespace std;
class Solution {
public:
	int numDecodings(string s) {
		// empty string or leading zero means no way
		if (!s.size() || s.front() == '0') return 0;

		// r1 and r2 store ways of the last and the last of the last
		int r1 = 1, r2 = 1;

		for (int i = 1; i < s.size(); i++) {
			// zero voids ways of the last because zero cannot be used separately
			if (s[i] == '0') r1 = 0;

			// possible two-digit letter, so new r1 is sum of both while new r2 is the old r1
			if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
				r1 = r2 + r1;
				r2 = r1 - r2;
			}

			// one-digit letter, no new way added
			else {
				r2 = r1;
			}
		}

		return r1;
	}
};
int main1()
{
	int test = Solution().numDecodings("12312434");
	system("pause");
	return 0;
}