#include <iostream>
#include <string>
#include <vector>
#include <stack> 
#include <queue>
using namespace std;
int main0()
{
	queue<int> Q;
	cout << sizeof(Q) << endl;//20
	cout << Q.size() << endl;//0
	cout << boolalpha << Q.empty() << endl;//队列Q为空，返回true

	Q.push(1);Q.push(2);Q.push(3);//队列：1 2 3
	cout << Q.size() << endl;//3
	cout << Q.front() << endl;//输出队首：1
	Q.pop();//移除队首元素
	cout << Q.front() << endl;//输出队首：2


	stack<int> S;
	cout << sizeof(S) << endl;//20
	cout <<boolalpha<< S.empty() << endl;//栈S为空，返回true
	S.push(3);//3
	S.push(7);//3 7
	S.push(1);//3 7 1
	cout << S.size() << " ";//栈大小为3

	cout << S.top() << " ";//输出栈顶元素：1
	S.pop();//移除栈顶元素，剩余3 7

	cout << S.top() << " ";//输出栈顶元素：7
	S.pop();//移除栈顶元素，剩余3

	cout << S.top() << " ";//输出栈顶元素：3
	S.push(5);//3 5

	cout << S.top() << " ";//输出栈顶元素：5
	S.pop();//移除栈顶元素，剩余3

	cout << S.top() << endl;//输出栈顶元素：3
	cout << boolalpha << S.empty() << endl;//栈S不为空，返回false
	S.emplace(2);

	vector<int> test1;
	cout<< sizeof(test1)<<endl;//16
	cout << test1.size() << endl;//0

	vector<int> test3(5);
	cout << sizeof(test3) << endl;//16
	cout << test3.size() << endl;//5

	test1.push_back(1);//1
	test3.push_back(1);//0 0 0 0 0 1

	test1.pop_back();//无返回值，去掉最后一个元素

	string str = "hello";
	//const char*p = str.data();
	char*p = (char*)str.data();
	char*q = "abc";
	*p = 'a';
	//*q = 'x';
	cout << "str:"<<str << endl;
	cout <<"p:" <<p << endl;
	cout << "*p:" << *p << endl;
	cout << "*q:" << *q << endl;
	cout << "q:" << q << endl;
	system("pause");
	return 0;
}