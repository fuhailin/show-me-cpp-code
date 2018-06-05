#include <iostream>
#include <string>
using namespace std;

string intToRoman(int num) {
	string M[] = { "","M","MM","MMM"};
	string D[] = { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
	string X[] = { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
	string I[] = { "","I","II","III","IV","V","VI","VII","VIII","IX" };
	string result = M[num / 1000] + D[(num % 1000) / 100] + X[((num % 1000) % 100) / 10] + I[(((num % 1000) % 100)%10)];
	return result;
}

int main12()
{
	cout << intToRoman(58);
	system("pause");
	return 0;
}