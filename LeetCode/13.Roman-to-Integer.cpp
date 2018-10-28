#include <iostream>
#include <map>
using namespace std;

int romanToInt(string s) {
	int result = 0;
	map<string, int> roman;
	roman.insert(pair<string, int>("M",1000));
	roman.insert(pair<string, int>("MM", 2000));
	roman.insert(pair<string, int>("MMM", 3000));

	roman.insert(pair<string, int>("C", 100));
	roman.insert(pair<string, int>("CC", 200));
	roman.insert(pair<string, int>("CCC", 300));
	roman.insert(pair<string, int>("CD", 400));
	roman.insert(pair<string, int>("D", 500));
	roman.insert(pair<string, int>("DC", 600));
	roman.insert(pair<string, int>("DCC", 700));
	roman.insert(pair<string, int>("DCCC", 800));
	roman.insert(pair<string, int>("CM", 900));

	roman.insert(pair<string, int>("X", 10));
	roman.insert(pair<string, int>("XX", 20));
	roman.insert(pair<string, int>("XXX", 30));
	roman.insert(pair<string, int>("XL", 40));
	roman.insert(pair<string, int>("L", 50));
	roman.insert(pair<string, int>("LX", 60));
	roman.insert(pair<string, int>("LXX", 70));
	roman.insert(pair<string, int>("LXXX", 80));
	roman.insert(pair<string, int>("XC", 90));

	roman.insert(pair<string, int>("I", 1));
	roman.insert(pair<string, int>("II", 2));
	roman.insert(pair<string, int>("III", 3));
	roman.insert(pair<string, int>("IV", 4));
	roman.insert(pair<string, int>("V", 5));
	roman.insert(pair<string, int>("VI", 6));
	roman.insert(pair<string, int>("VII", 7));
	roman.insert(pair<string, int>("VIII", 8));
	roman.insert(pair<string, int>("IX", 9));
	//int test = s.length;
	int test1 = s.length();
	while (s.length())
	{
		string tmp = s;
		while (roman.find(tmp)==roman.end())
		{
			tmp.pop_back();
		}
		result = result + roman[tmp];
		s = s.erase(0, tmp.length());
	}
	return result;
}

int main13()
{
	cout << romanToInt("MCMXCIV");
	system("pause");
	return 0;
}