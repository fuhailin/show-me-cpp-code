#include <iostream>
using namespace std;
class Line
{
public:
	Line();//构造函数
	Line(double len);  // 这是构造函数
	~Line();//析构函数
	void setLength(double len);
	double getLength();

private:
	double length;
};

Line::Line()
{
	cout << "欢饮来到Line的构造函数！" << endl;
}
Line::Line(double len)
{
	cout << "欢饮来到Line="<<len<<"的构造函数！" << endl;
}

Line::~Line()
{
	cout << "欢迎来到Line的析构函数！" << endl;
}
void Line::setLength(double len)
{
	length = len;
}
double Line::getLength()
{
	return length;
}
int main0()
{
	//Line *line;//如果定义为指针，将会因为没有初始化而报错
	Line line1;
	Line line2(10.6);
	line1.setLength(12.04);
	cout << line1.getLength() << endl;
	system("pause");
	return 0;
}