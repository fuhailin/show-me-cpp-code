#include <iostream>
using namespace std;
#define maxSize 100
/*  ����ͼ�ı߽ṹ  */
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	int info;
}ArcNode;
/*  ����ͼ�Ķ���ṹ  */
typedef struct VNode 
{
	char data;
	ArcNode *firstarc;
}VNode;
/*  ����ͼ���ڽӱ�ṹ  */
typedef struct
{
	VNode adjlist[maxSize];		//��ӱ�
	int n, e;					//�������ͱ���
}AGraph;

//struct AGraph* createGraph()
//{
//
//};

int main5()
{
	return 0;
}