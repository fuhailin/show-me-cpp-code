#include <iostream>
using namespace std;
class Line
{
public:
	Line();//���캯��
	Line(double len);  // ���ǹ��캯��
	~Line();//��������
	void setLength(double len);
	double getLength();

private:
	double length;
};

Line::Line()
{
	cout << "��������Line�Ĺ��캯����" << endl;
}
Line::Line(double len)
{
	cout << "��������Line="<<len<<"�Ĺ��캯����" << endl;
}

Line::~Line()
{
	cout << "��ӭ����Line������������" << endl;
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
	//Line *line;//�������Ϊָ�룬������Ϊû�г�ʼ��������
	Line line1;
	Line line2(10.6);
	line1.setLength(12.04);
	cout << line1.getLength() << endl;
	system("pause");
	return 0;
}