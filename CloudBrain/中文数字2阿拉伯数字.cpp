#include <iostream>
#include <map>
#include <string>
using namespace std;

int chineseNum2num(wstring s)
{
	map<wchar_t, int> chineseNum;
	chineseNum.insert(pair<wchar_t, int>(L'零', 0));
	chineseNum.insert(pair<wchar_t, int>(L'一', 1));
	chineseNum.insert(pair<wchar_t, int>(L'二', 2));
	chineseNum.insert(pair<wchar_t, int>(L'三', 3));
	chineseNum.insert(pair<wchar_t, int>(L'四', 4));
	chineseNum.insert(pair<wchar_t, int>(L'五', 5));
	chineseNum.insert(pair<wchar_t, int>(L'六', 6));
	chineseNum.insert(pair<wchar_t, int>(L'七', 7));
	chineseNum.insert(pair<wchar_t, int>(L'八', 8));
	chineseNum.insert(pair<wchar_t, int>(L'九', 9));
	chineseNum.insert(pair<wchar_t, int>(L'十', 10));
	chineseNum.insert(pair<wchar_t, int>(L'百', 100));
	chineseNum.insert(pair<wchar_t, int>(L'千', 1000));
	chineseNum.insert(pair<wchar_t, int>(L'万', 10000));
	chineseNum.insert(pair<wchar_t, int>(L'亿', 100000000));
	chineseNum.insert(pair<wchar_t, int>(L'壹', 1));
	chineseNum.insert(pair<wchar_t, int>(L'贰', 2));
	chineseNum.insert(pair<wchar_t, int>(L'叁', 3));
	chineseNum.insert(pair<wchar_t, int>(L'肆', 4));
	chineseNum.insert(pair<wchar_t, int>(L'伍', 5));
	chineseNum.insert(pair<wchar_t, int>(L'陆', 6));
	chineseNum.insert(pair<wchar_t, int>(L'柒', 7));
	chineseNum.insert(pair<wchar_t, int>(L'捌', 8));
	chineseNum.insert(pair<wchar_t, int>(L'玖', 9));
	chineseNum.insert(pair<wchar_t, int>(L'拾', 10));
	chineseNum.insert(pair<wchar_t, int>(L'玖', 100));
	chineseNum.insert(pair<wchar_t, int>(L'仟', 1000));
	chineseNum.insert(pair<wchar_t, int>(L'萬', 10000));
	chineseNum.insert(pair<wchar_t, int>(L'億', 100000000));

	int result=0, tmp = 0, hnd_mln=0;
	wchar_t curr_char;
	int curr_digit;
	for (int i = 0; i < s.length(); ++i)
	{
		curr_char = s.at(i);
		if (chineseNum.find(curr_char) == chineseNum.end())
			return NULL;
		curr_digit = chineseNum.at(curr_char);

		if (curr_digit == pow(10, 8))//meet 「亿」 or 「億」
		{
			result = result + tmp;
			result = result * curr_digit;
			//get result before 「亿」 and store it into hnd_mln
			//reset `result`
			hnd_mln = hnd_mln * pow(10, 8) + result;
			result = 0;
			tmp = 0;
		}
		else
		{
			if (curr_digit == pow(10, 4))//meet 「万」 or 「萬」
			{
				result = result + tmp;
				result = result * curr_digit;
				tmp = 0;
			}
			else
			{
				if (curr_digit >= 10)//meet 「十」, 「百」, 「千」 or their traditional version
				{
					if (tmp == 0)
						tmp = 1;
					result = result + curr_digit * tmp;
					tmp = 0;
				}
				else
				{
					tmp = tmp * 10 + curr_digit;
					/*if (curr_digit != NULL)
						
					else
					{
						return result;
					}*/
				}
			}
		}
	}
	result = result + tmp;
	result = result + hnd_mln;
	return result;
}

template <class T>

int getArrayLen(T& array)

{//使用模板定义一 个函数getArrayLen,该函数将返回数组array的长度

	return (sizeof(array) / sizeof(array[0]));
}


int main()
{
	/*wstring test;
	wcin >> test;
	wcout << test << endl;*/

	wcout.imbue(locale("chs"));
	/*wstring test1 = L"华师";
	wcout << test1 << endl;*/

	

	wstring testdict[] = { L"哈十八",L"五十八", L"一百二十三万四千五百六十七" ,L"三千二百一十万零二百一十五" ,L"一亿零九十万零七十六" };
	for (int i = 0; i < getArrayLen(testdict); ++i)
	{
		wcout << testdict[i] << '\t' << chineseNum2num(testdict[i]) << endl;
	}
	system("pause");
	return 0;
}