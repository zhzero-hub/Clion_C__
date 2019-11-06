///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//1、用邻接表创建有向图；
//2、设计递归算法寻找所有通过指定节点的简单回路
//3、设计算法判断从顶点u到顶点v是否存在路径（分析时间复杂度）
//4、设计算法计算所有顶点的入度（分析时间复杂度）
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct arcnode
{
    int index;//邻接点序号
    struct arcnode *next;
}AR;

typedef struct MyGraph
{
    int type;//0，表示无向图，1表示有向图
    int arcnum,vexnum;//图中边的个数以及顶点个数
    char **vexname;//存放顶点名的二维数组
    AR *N;//存放邻接表头结点的数组
}GH;

int findvex(char *s,GH *G);//确定顶点s对应的序号
void creatgraph(GH *G);//以邻接表的形式创建图
void showgraph(GH *G);//以邻接表的形式显示图
void findpath(GH *G,char *start);//寻找所有经过顶点start的简单路径
int ispath(GH *G,char *start,char *end);//判断从顶点start到顶点end是否存在路径，存在返回1，否则返回0
void indegree(GH *G);//计算并显示输出图中每个顶点的入度
int menu_select();


int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.创建有向图（邻接表）\n");
        printf("2.输出所有经过指定顶点的简单回路\n");
        printf("3.判断两个顶点之间是否存在路径\n");
        printf("4.输出所有顶点的入度\n");
        printf("0.exit\n");
        printf("Please input index(0-4):");
        i=getchar();
    }while(i<'0' || i>'4');
    return (i-'0');
}

main()
{
    GH G;
    char c1[20],c2[20];
    for(;;)
    {
        switch(menu_select())
        {
            case 1:
                creatgraph(&G);
                showgraph(&G);
                system("pause");
                break;
            case 2:
                showgraph(&G);
                printf("请输入顶点名:\n");
                scanf("%s",c1);
                printf("所有经过%s的简单回路有:\n",c1);
                findpath(&G,c1);
                system("pause");
                break;
            case 3:
                showgraph(&G);
                printf("请输入起止两个顶点名:\n");
                scanf("%s%s",c1,c2);
                if(ispath(&G,c1,c2))
                    printf("从顶点%s到顶点%s存在路径\n",c1,c2);
                else
                    printf("从顶点%s到顶点%s不存在路径\n",c1,c2);
                system("pause");
                break;
            case 4:
                showgraph(&G);
                printf("\n图中所有顶点的入度:\n");
                indegree(&G);
                system("pause");
                break;
            case 0:
                printf("GOOD BYE\n");
                system("pause");
                exit(0);
        }
    }
}




int findvex(char *s,GH *G)//根据顶点名确定该顶点的编号
{
    int i;
    for(i=0;i<G->vexnum;i++)
    {
        if(strcmp(s,G->vexname[i])==0)
            return i;
    }
    printf("read file erro\n");
    exit(-1);
}

void creatgraph(GH *G)
{
////////////////////////完成该函数///////////////////////////////////////////////
    char filename[]="graph1.txt";


}



void showgraph(GH *G)
{
    int i;
    AR *p;
    for(i=0;i<G->vexnum;i++)
    {
        printf("\n%s ",G->vexname[i]);
        p=G->N[i].next;
        while(p)
        {
            printf("--%s ",G->vexname[p->index]);
            p=p->next;
        }
    }
    printf("\n");
}


void findpath(GH *G,char *start)//寻找所有经过顶点start的简单回路
{
////////////////////////完成该函数///////////////////////////////////////////////


}

void indegree(GH *G)//计算并显示输出图中每个顶点的入度
{
////////////////////////完成该函数///////////////////////////////////////////////

}

int ispath(GH *G,char *start,char *end)//判断从顶点start到顶点end是否存在路径，存在返回1，否则返回0
{
///////////////////////完成该函数///////////////////////////////////////////////

}






