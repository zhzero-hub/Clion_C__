/*****************************************************************************************
*  �½ڣ��γ���Ʊ����������
*  ��Ŀ:��С������ (����) ��ͼ��
*	[��������]
*	��������ķ�㷨�Ϳ�³˹�����㷨ʵ����С���������⡣
*	[����Ҫ��]
*	��1�����н���ͼ�������ļ�����һ���Ƕ��������Ȼ�������Ƕ��������������Ǳߣ���float��ʾ�ߵ�Ȩֵ��
*	��2�����ڽӱ�����ڽӾ����ʾͼ�Կɣ�
*	��3���ֱ�����prim��Kruskal�㷨ʵ����С��������
*	��4�������С��������Ȩֵ֮�ͣ������õı�
*  ���ߣ�������
*  ���� ��2019��12��19
********************************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define INFINTY INT_MAX		//���ֵΪ��
#define MAX_VERTEX_NUM 20	//��󶥵���
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
    VertexType adjvex;		//��Ŷ���
    VRType lowcost;			//�����С��Ȩֵ
};

typedef struct ArcCell
{
    VRType adj;//VRType�Ƕ���Ĺ�ϵ���ͣ�����Ȩͼʹ��0 1��ʾ�Ƿ����ڣ���Ȩͼ��ʾȨֵ
    InfoType *info;//�洢�����Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];//��������
    AdjMatrix arcs;					//�ڽӾ���
    int vexnum, arcnum;				//ͼ�ĵ�ǰ�������ͻ���
    int IncInfo;					//IncInfo��Ϊ0��������ýڵ㲻��������Ϣ
    GraphKind kind;					//ͼ�����ͱ�־
}MGraph;

//���ͼG�к��ж���V�򷵻ظö�����ͼG�е�λ�ã����򷵻�������Ϣ
int LocateVex(MGraph G, VertexType u)
{
    for(int i=0; i<G.vexnum; i++)
    {
        if(G.vexs[i] == u)
            return i;
    }
    return -1;
}

//��ӡ��ͼG����Ӿ���
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

//����������G
Status CreateUDN(MGraph &G, FILE *file)
{
    char v1, v2;
    int i = 0, j = 0, k = 0, num = 0, n = 0;
    char ch;
    VRType w = 0;

    G.IncInfo = 0;

    fscanf(file, "%d", &G.vexnum);				//������
    ch = fgetc(file);

    for(i = 0; i<G.vexnum; i++)					//��ʼ���ڽӾ���
    {
        for(int j=0; j<G.vexnum;j++)
        {
            G.arcs[i][j].adj = INFINTY;
            G.arcs[i][j].info = NULL;
        }
    }

    for(i = 0; i < G.vexnum; i++)				//����������������
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
//		fscanf(file, " %s,%s,%d\n", &v1, &v2, &w);//����һ���������Ķ��㼰Ȩֵ

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
    printf("ͼG���ڽӾ���Ϊ��\n");
    Print(G);

    return OK;
}

/*����min������Ȩֵ��С�Ķ������*/
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

/*-------------------------------Prim�㷨����С������----------------------------------------*/
/*������ӵ�u���������������G����С������T*/
int MiniSpanTree(MGraph G, VertexType u)
{
    int i = 0, j = 0, k = 0, w = 0, num = 0;
    MinTree min[MAX_VERTEX_NUM];		//�������飬�����С���۵ı߼���Ȩֵ

    k = LocateVex(G, u);				//kΪ����u����G�е����
    for(int j = 0; j < G.vexnum; j++)	//��ʼ����������
    {
        if(j != k)
        {
            min[j].adjvex = u;
            min[j].lowcost = G.arcs[k][j].adj;
        }
    }

    min[k].lowcost = 0;					//������k����������С�������Ķ��㼯��
    printf("��С���������õıߣ�\n");
    for(int i = 1; i < G.vexnum; i++)	//��ʣ�ඥ���м�������С������
    {
        k = MiniMum(G, min);			//�����С����������һ���������k
        num += min[k].lowcost;			//��Ȩ
//		printf("%s -- %s", G.vexs[k], min[k].adjvex);
        min[k].lowcost = 0;				//������k����������С�������Ķ��㼯��
        for(j = 0; j < G.vexnum; j++)	//�����㲢�붥�㼯�����¼���������С��
        {
            if(G.arcs[k][j].adj < min[j].lowcost)
            {
                min[j].adjvex = k;
                min[j].lowcost = G.arcs[k][j].adj;
            }
        }
    }

    printf("��С��������Ȩֵ֮��Ϊ��%d\n", num);

    return 0;
}

int main()
{
    MGraph G;
    FILE *file;

    if((file = fopen("Graph.txt", "r")) == NULL)
    {
        printf("�ļ���ʧ�ܣ�");
        exit(OVERFLOW);
    }
    CreateUDN(G, file);				//�����ļ�Graph.txt����һ��������
    printf("Prim�㷨����С��������\n");
    MiniSpanTree(G, 1);

    fclose(file);
    return 0;
}
