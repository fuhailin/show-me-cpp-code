#include <iostream>
#include <map>
using namespace std;

int main7() {
  map<char, int> chineseNum;
  chineseNum.insert(pair<char, int>('A', 0));
  chineseNum['B'] = 1;

  map<char, int>::iterator iter;
  iter = chineseNum.find('C');  // iter Ϊ end
  iter = chineseNum.find('A');  //ȡ��keyΪ'A'�ļ�ֵ�ԣ�iter Ϊ ('A', 0)
  cout << iter->first << '\t' << iter->second << endl;

  int tmp = chineseNum['C'];  // F����map�У��Ὣ('F',0)���ӽ�map��������0
  cout << chineseNum.size() << endl;                          // 3
  if (chineseNum.find('C') != chineseNum.end()) cout << 'C';  // C

  //�������h��
  iter = chineseNum.find('C');
  chineseNum.erase(iter);

  //���P�I�քh��
  int n = chineseNum.erase('B');  //����h���˕�����1����t����0

  //�õ����������h�� : ������map���
  chineseNum.erase(chineseNum.begin(), chineseNum.end());
  //��ͬ�chineseNum.clear()

  system("pause");
  return 0;
}