#include<iostream>
#include<map>
using namespace std;

int main7()
{
	map<char, int> chineseNum;
	chineseNum.insert(pair<char, int>('A', 0));
	chineseNum['B'] = 1;

	map<char, int>::iterator iter;
	iter = chineseNum.find('C'); //iter 为 end
	iter = chineseNum.find('A');//取出key为'A'的键值对，iter 为 ('A', 0)
	cout << iter->first << '\t' << iter->second << endl;

	int tmp = chineseNum['C'];//F不在map中，会将('F',0)添加进map，并返回0
	cout << chineseNum.size() << endl;//3
	if (chineseNum.find('C') != chineseNum.end())
		cout << 'C';//C

	//迭代器刪除
	iter = chineseNum.find('C');
	chineseNum.erase(iter);

	//用關鍵字刪除
	int n = chineseNum.erase('B');//如果刪除了會返回1，否則返回0

									 //用迭代器範圍刪除 : 把整個map清空
	chineseNum.erase(chineseNum.begin(), chineseNum.end());
	//等同於chineseNum.clear()

	system("pause");
	return 0;
}