///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//1、用邻接矩阵创建无向网；
//2、请判断该无向网是否连通，是否包含回路（分析时间复杂度）
//3、输出任意两个顶点之间的所有简单路径，以及各自的路径长度（路径长度指的是路径中所有边的权值之和）
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int maxx = 9999999;//定义的无穷大值

typedef struct MyGraph
{
    int type;//0，表示无向网，1表示有向网
    int arcnum = 0,vexnum = 0;//图中边的个数以及顶点个数
    char vexname[20][20];//存放顶点名的二维数组
    int A[20][20];//邻接矩阵，A[i][j]表示i号顶点与j号顶点之间边的权值，若i,j之间没有边，则A[i][j]取值无穷大
}GH;
int menu_select();
int findvex(char *s,GH *G);//确定顶点s对应的序号
void creatgraph(GH *G);//以邻接矩阵的形式创建图
void showgraph(GH *G);//以邻接表的形式显示图
void findpath(GH *G,char *start,char *end);//寻找简单路径
int iscycle(GH *G);//判断图中是否有回路，有返回1，否则返回0
int isconnect(GH *G);//判断图是否连通，是返回1，否则返回0

int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.创建无向网（邻接矩阵）\n");
        printf("2.判断无向网是否连通\n");
        printf("3.判断无向网中是否有回路\n");
        printf("4.输出任意两个顶点之间的所有简单路径以及路径长度\n");
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
                if(isconnect(&G))
                    printf("\n该图是连通的\n");
                else
                    printf("\n该图不是连通的\n");
                system("pause");
                break;
            case 3:
                showgraph(&G);
                if(iscycle(&G))
                    printf("\n该图中包含回路\n");
                else
                    printf("\n该图中不包含回路\n");
                system("pause");
                break;
            case 4:
                showgraph(&G);
                printf("\n请输入起止两个顶点名:\n");
                scanf("%s%s",c1,c2);
                printf("所有从 %s 到 %s 的简单路径以及路径长度：\n",c1,c2);
                findpath(&G,c1,c2);
                system("pause");
                break;
            case 0:
                printf("GOOD BYE\n");
                system("pause");
                exit(0);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int findvex(char *s,GH *G)
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
    char filename[]="graph2.txt";
    ifstream file(filename);
    if(file.fail())
    {
        cout << "文件打开失败" << endl;
        exit(0);
    }
    file >> G->vexnum;
    for(int i = 0;i < G->vexnum;i ++)file >> G->vexname[i];
    for(int i = 0;i < G->vexnum;i ++)for(int j = 0;j < G->vexnum;j ++)G->A[i][j] = maxx;
    while(!file.eof())
    {
        char p[20] , q[20];
        int data;
        file >> p >> q >> data;
        int p_pos = findvex(p , G);
        int q_pos = findvex(q , G);
        G->A[p_pos][q_pos] = G->A[q_pos][p_pos] = data;
        G->arcnum ++;
    }
    file.close();
}



void showgraph(GH *G)
{
    int i,j;
    for(i=0;i<G->vexnum;i++)
    {
        printf("\n%s",G->vexname[i]);
        for(j=0;j<G->vexnum;j++)
        {
            if(G->A[i][j]<maxx)
                printf("--%s(%d) ",G->vexname[j],G->A[i][j]);
        }
    }
    printf("\n");
}



void Find(GH *G , char *end , int j , int *visit , vector<char *> &path)
{
    if(strcmp(G->vexname[j] , end) == 0)
    {
        for(const auto &x: path)cout << x << "    ";
        cout << endl;
        return;
    }
    int pos = 0;
    while(pos < G->vexnum)
    {
        if(G->A[j][pos] != maxx && visit[pos] == 0)
        {
            visit[pos] = 1;
            path.push_back(G->vexname[pos]);
            Find(G , end , pos , visit , path);
            path.pop_back();
            visit[pos] = 0;
            pos ++;
        }
        else pos ++;
    }
}

void findpath(GH *G,char *start,char *end)//寻找简单路径函数
{
    int pos = findvex(start , G);
    int visit[20] = {};
    visit[pos] = 1;
    vector<char *>path;
    path.push_back(start);
    Find(G , end , pos , visit , path);
}


int iscycle(GH *G)//判断图中是否有回路，有返回1，否则返回0
{
    int t[20][20];
    int visit[20] = {};
    int top = G->vexnum;
    vector<int> ans;
    int num = 0;
    for(int i = 0;i < top;i ++)for(int j = 0;j < top;j ++)t[i][j] = G->A[i][j];
    for(int i = 0;i < top;i ++)
    {
        int sum = 0;
        for(int j = 0;j < top;j ++)if(t[i][j] != maxx)sum ++;
        if(sum <= 1)
        {
            ans.push_back(i);
            visit[i] = 1;
            for(int j = 0;j < top;j ++)if(t[i][j] != maxx)t[i][j] = t[j][i] = maxx;
        }
    }
    while(!ans.empty())
    {
        num ++;
        ans.pop_back();
        for(int i = 0;i < top;i ++)
        {
            if(visit[i])continue;
            int sum = 0;
            for(int j = 0;j < top;j ++)if(t[i][j] != maxx)sum ++;
            if(sum <= 1)
            {
                ans.push_back(i);
                visit[i] = 1;
                for(int j = 0;j < top;j ++)if(t[i][j] != maxx)t[i][j] = t[j][i] = maxx;
            }
        }
    }
    return num != top;
}


int isconnect(GH *G)//判断图是否连通，是返回1，否则返回0
{
///////////////////////////完成该函数////////////////////////////////


}





