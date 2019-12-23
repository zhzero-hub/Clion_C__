/*****************************************************************************************
*  章节：课程设计必做题第六题
*  题目:最小生成树 (必做) （图）
*	[问题描述]
*	利用普利姆算法和克鲁斯卡尔算法实现最小生成树问题。
*	[基本要求]
*	（1）自行建立图的数据文件，第一行是顶点个数，然后依次是顶点名，接下来是边，用float表示边的权值；
*	（2）以邻接表或者邻接矩阵表示图皆可；
*	（3）分别利用prim和Kruskal算法实现最小生成树；
*	（4）输出最小生成树的权值之和，及所用的边
*  作者：范文鑫
*  日期 ：2019年12月19
********************************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define INFINTY INT_MAX		//最大值为∞
#define MAX_VERTEX_NUM 20	//最大顶点数
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef enum{DG=1, DN, UDG, UDN}GraphKind;
typedef int VRType;
typedef char VertexType;
typedef int InfoType;

struct MinTree
{
    VertexType adjvex;		//存放顶点
    VRType lowcost;			//存放最小的权值
};

typedef struct ArcCell
{
    VRType adj;//VRType是顶点的关系类型，对无权图使用0 1表示是否相邻，有权图表示权值
    InfoType *info;//存储相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];//顶点向量
    AdjMatrix arcs;					//邻接矩阵
    int vexnum, arcnum;				//图的当前顶点数和弧数
    int IncInfo;					//IncInfo若为0，则表明该节点不含其他信息
    GraphKind kind;					//图的类型标志
}MGraph;

//如果图G中含有顶点V则返回该顶点在图G中的位置，否则返回其他信息
int LocateVex(MGraph G, VertexType u)
{
    for(int i=0; i<G.vexnum; i++)
    {
        if(G.vexs[i] == u)
            return i;
    }
    return -1;
}

//打印出图G的领接矩阵
void Print(MGraph G)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            printf("%d\t", G.arcs[i][j].adj);
        }
        printf("\n");
    }
    return;
}

//构造无向网G
Status CreateUDN(MGraph &G, FILE *file)
{
    char v1, v2;
    int i = 0, j = 0, k = 0, num = 0, n = 0;
    char ch;
    VRType w = 0;

    G.IncInfo = 0;

    fscanf(file, "%d", &G.vexnum);				//顶点数
    ch = fgetc(file);

    for(i = 0; i<G.vexnum; i++)					//初始化邻接矩阵
    {
        for(int j=0; j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = INFINTY;
            G.arcs[i][j].info = NULL;
        }
    }

    for(i = 0; i < G.vexnum; i++)				//输入各个顶点的名称
    {
        fscanf(file, "%s", &G.vexs[i]);
        ch = fgetc(file);
    }

    fscanf(file, "%d", &G.arcnum);
    ch = fgetc(file);

    for(k = 0; k < G.arcnum; k++)
    {

        fscanf(file, "%c", &v1);
        fscanf(file, "%c", &v2);
        fscanf(file, "%d\n",&w);
//		fscanf(file, " %s,%s,%d\n", &v1, &v2, &w);//输入一条边依附的顶点及权值

        i = LocateVex(G,v1);
//		if(i == -1)
//		{
//			G.vexs[num] = v1;
//			i = num;
//			num++;
//		}
        j = LocateVex(G,v2);
//		if(j == -1)
//		{
//			G.vexs[num] = v2;
//			j = num;
//			num++;
//		}
        G.arcs[i][j].adj = w;
        G.arcs[j][i].adj = w;
//		printf("%d,%d,%d\n",i,j,w,G.arcs[i][j].adj);
    }
    printf("图G的邻接矩阵为：\n");
    Print(G);

    return OK;
}

/*返回min数组中权值最小的顶点序号*/
int MiniMum(MGraph G, MinTree *min)
{
    int i = 0, j = 0,k =0, w = INFINTY;
    while(!min[k].lowcost)
        k++;
    w = min[k].lowcost;
    j = k;
    for(int i = k + 1; i < G.vexnum; i++)
    {
        if(min[i].lowcost > 0)
        {
            if(w > min[i].lowcost)
            {
                printf("w = %d, min = %d\n", w,min[i].lowcost);
                w = min[i].lowcost;
                j = i;
            }
        }
    }

    return j;
}

/*-------------------------------Prim算法求最小生成树----------------------------------------*/
/*计算出从第u个顶点出发构造网G的最小生成树T*/
int MiniSpanTree(MGraph G, VertexType u)
{
    int i = 0, j = 0, k = 0, w = 0, num = 0;
    MinTree min[MAX_VERTEX_NUM];		//辅助数组，存放最小代价的边及其权值

    k = LocateVex(G, u);				//k为顶点u在于G中的序号
    for(int j = 0; j < G.vexnum; j++)	//初始化辅助数组
    {
        if(j != k)
        {
            min[j].adjvex = u;
            min[j].lowcost = G.arcs[k][j].adj;
        }
    }

    min[k].lowcost = 0;					//将顶点k并入待求出最小生成树的顶点集里
    printf("最小生成树所用的边：\n");
    for(int i = 1; i < G.vexnum; i++)	//在剩余顶点中继续求最小生成树
    {
        k = MiniMum(G, min);			//求出最小生成树的下一个顶点序号k
        num += min[k].lowcost;			//加权
//		printf("%s -- %s", G.vexs[k], min[k].adjvex);
        min[k].lowcost = 0;				//将顶点k并入待求出最小生成树的顶点集里
        for(j = 0; j < G.vexnum; j++)	//将顶点并入顶点集后重新计算他的最小边
        {
            if(G.arcs[k][j].adj < min[j].lowcost)
            {
                min[j].adjvex = k;
                min[j].lowcost = G.arcs[k][j].adj;
            }
        }
    }

    printf("最小生成树的权值之和为：%d\n", num);

    return 0;
}

int main()
{
    MGraph G;
    FILE *file;

    if((file = fopen("Graph.txt", "r")) == NULL)
    {
        printf("文件打开失败！");
        exit(OVERFLOW);
    }
    CreateUDN(G, file);				//根据文件Graph.txt建立一个有向网
    printf("Prim算法求最小生成树：\n");
    MiniSpanTree(G, 1);

    fclose(file);
    return 0;
}
