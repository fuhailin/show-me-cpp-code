#include <iostream>
using namespace std;
#define maxSize 100
/*  建立图的边结构  */
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	int info;
}ArcNode;
/*  建立图的顶点结构  */
typedef struct VNode 
{
	char data;
	ArcNode *firstarc;
}VNode;
/*  建立图的邻接表结构  */
typedef struct
{
	VNode adjlist[maxSize];		//领接表
	int n, e;					//顶点数和边数
}AGraph;

//struct AGraph* createGraph()
//{
//
//};

int main5()
{
	return 0;
}