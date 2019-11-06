///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//1、用邻接表创建有向图；
//2、设计递归算法寻找所有通过指定节点的简单回路
//3、设计算法判断从顶点u到顶点v是否存在路径（分析时间复杂度）
//4、设计算法计算所有顶点的入度（分析时间复杂度）
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include <iostream>
#include <cstring>
#include <string>
#include <unordered_set>
#include <fstream>
#include <vector>
using namespace std;
typedef struct arcnode
{
    int index = -1;//邻接点序号
    struct arcnode *next = nullptr;
}AR;

typedef struct MyGraph
{
    int type = -1;//0，表示无向图，1表示有向图
    int arcnum = 0,vexnum = 0;//图中边的个数以及顶点个数
    char *vexname[20];//存放顶点名的二维数组
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

int main()
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
    printf("read file error\n");
    exit(-1);
}

void creatgraph(GH *G)
{
    char filename[]="graph1.txt";
    ifstream file(filename);
    if(file.fail())
    {
        cout << "文件打开失败" << endl;
        exit(0);
    }
    G->type = 0;
    file >> G->vexnum;
    G->N = (AR *)malloc(G->vexnum * sizeof(AR));
    for(int i = 0;i < G->vexnum;i ++)
    {
        G->vexname[i] = (char *)malloc(20 * sizeof(char));
        file >> G->vexname[i];
        G->N[i].index = i;
        G->N[i].next = nullptr;
    }
    while(!file.eof())
    {
        char p[20] , q[20];
        file >> p >> q;
        int pos = findvex(p , G);
        int data = findvex(q , G);
        AR *x = &G->N[pos];
        while(x->next != nullptr)x = x->next;
        AR *temp = (AR *)malloc(sizeof(AR));
        temp->next = nullptr;
        temp->index = data;
        x->next = temp;
        G->arcnum ++;
    }
    file.close();
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

void Find(GH *G , char *start , AR *x , int *visit , vector<char *> &path)
{
    if(strcmp(G->vexname[x->index] , start) == 0)
    {
        for(const auto &y: path)cout << y << "----";
        cout << start << endl;
    }
    if(visit[x->index] == 0)
    {
        visit[x->index] = 1;
        path.push_back(G->vexname[x->index]);
        Find(G , start , &G->N[x->index] , visit , path);
        visit[x->index] = 0;
        path.pop_back();
    }
    if(x->next != nullptr)
    {
        x = x->next;
        Find(G , start , x , visit , path);
    }
}


void findpath(GH *G,char *start)//寻找所有经过顶点start的简单回路
{
    int visit[20] = {};
    vector<char *> path;
    int pos = findvex(start , G);
    visit[pos] = 1;
    path.push_back(start);
    AR *x = &G->N[pos];
    x = x->next;
    if(x == nullptr)cout << "该点为孤立点" << endl;
    Find(G , start , x , visit , path);
}

void indegree(GH *G)//计算并显示输出图中每个顶点的入度
{
    int ans[20] = {};
    for(int i = 0;i < G->vexnum;i ++)
    {
        AR *x = &G->N[i];
        x = x->next;
        while(x != nullptr)
        {
            ans[x->index] ++;
            x = x->next;
        }
    }
    for(int i = 0;i < G->vexnum;i ++)cout << G->vexname[i] << "的入度为: " << ans[i] << endl;
}

void find(GH *G , char *end , AR *x , int *visit , int &ans)
{
    if(strcmp(G->vexname[x->index] , end) == 0)
    {
        ans = 1;
        return;
    }
    if(!ans && visit[x->index] == 0)
    {
        visit[x->index] = 1;
        find(G , end , &G->N[x->index] , visit , ans);
        visit[x->index] = 0;
    }
    if(!ans && x->next != nullptr)
    {
        x = x->next;
        find(G , end , x , visit , ans);
    }
}

int ispath(GH *G,char *start,char *end)//判断从顶点start到顶点end是否存在路径，存在返回1，否则返回0
{
    int visit[20] = {};
    int pos = findvex(start , G);
    visit[pos] = 1;
    AR *x = &G->N[pos];
    x = x->next;
    int ans = 0;
    find(G , end , x , visit , ans);
    return ans;
}






