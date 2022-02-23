#include <iostream>
using namespace std;
class Solution
{
public:
	bool g_InvalidInput = false;
	double Power(double base, int exponent) {
		g_InvalidInput = false;
		if (equal(base, 0.0) && exponent < 0)
		{
			g_InvalidInput = true;
			return 0.0;
		}
		unsigned int absExponent = (unsigned int)(exponent);
		if (exponent < 0)
			absExponent = (unsigned int)(-exponent);
		double result = PowerWithUnsignedExponent(base, absExponent);
		if (exponent < 0)
			return 1.0 / result;
		return result;
			
	}
	double PowerWithUnsignedExponent(double base, int exponent)
	{
		if (exponent == 0)
			return 1;
		if (exponent == 1)
			return base;
		double result = PowerWithUnsignedExponent(base, exponent >> 1);
		result *= result;
		if (exponent & 0x1 == 1)
			result *= base;
		return result;
	}
	bool equal(double num1,double num2)
	{
		if ((num1 - num2) > -0.0000001 && (num1 - num2) < 0.0000001)
			return true;
		else
			return false;
	}

};

int main7()
{



	cout << Solution().Power(2.5, -2) << endl;
	system("pause");
	return 0;
}