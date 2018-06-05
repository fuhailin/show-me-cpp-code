#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

int lengthOfLongestSubstring(string s) {
	if (s.length() == 0)
		return 0;
	map<char, int> _map;
	int res = 0;
	int left = 0;
	for (int i = 0; i != s.length(); i++)
	{
		if (_map.find(s[i]) != _map.end())
		{
			int test = _map[s[i]];
			left = max(_map[s[i]]+1, left);
		}
		_map[s[i]] = i;
		res = max(res, i - left+1);
	}
	return res;
}

int main3()
{
	cout << lengthOfLongestSubstring("pwwkew") << endl;
	system("pause");
	return 0;
}