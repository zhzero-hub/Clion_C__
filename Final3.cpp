/////////////////////////////////////////////////////////////////////////////////////////
//
//              姓名：郑好
//              
//              学号：161820217
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
using namespace std;

typedef struct arc//邻接表的结点结构
{
	int index;
	struct arc *next;
}AR;

typedef struct MyGraph//定义图的结构
{
	int type;//
	int vexnum;//顶点个数
	char **vexname;//存放顶点的名字
	AR *N;//邻接表
}GH;



int findvex(char *s,GH *G);//确定顶点对应序号，将该序号返回
void creatgraph(GH *G);//创建以邻接矩阵表示的图
void showgraph(GH *G);//显示图
int isconect(GH *G);//判断图是否强连通，是返回1，否则返回0
void findfar(GH *G,char *start);//找出所有距离start最远的顶点



int main()
{
	char s[100];
	GH G;//定义图的变量
	creatgraph(&G);//创建图
	showgraph(&G);//显示图
	if(isconect(&G))
		printf("\n该图是强连通的\n");
	else
		printf("\n该图不是强连通的\n");
	printf("\n请输入顶点名:\n");
	cin >> s;//s表示一个顶点名，调用findfar函数输出所有与顶点s距离最远的顶点名（不包括与s不连通的顶点）
	while(strcmp(s,"#")!=0)
	{
		findfar(&G,s);
		printf("\n请输入顶点名:\n");
	    cin >> s;
	}			
}


int findvex(char *s,GH *G)
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
	FILE *fp;
	AR *p;
	int i,j,M;
	char c1[4],c2[4];
	if((fp=fopen("graph.txt","r"))==NULL)
	{
		printf("无法打开图的数据文件\n");
		exit(-1);
	}
	fscanf(fp,"%d",&M);
	G->vexnum=M;
	G->type=1;//有向图
	G->N=(AR *)malloc(M*sizeof(AR));
	G->vexname=(char **)malloc(M*sizeof(char *));
	for(i=0;i<M;i++)
	{		
		fscanf(fp,"%s",c1);
		G->vexname[i]=(char *)malloc((strlen(c1))*sizeof(char));
		strcpy(G->vexname[i],c1);
		G->N[i].next=NULL;		
	}    
	while(fscanf(fp,"%s%s",c1,c2)!=EOF)
	{
		i=findvex(c1,G);
		j=findvex(c2,G);
		p=(AR *)malloc(sizeof(AR));
		p->index=j;
		p->next=G->N[i].next;
		G->N[i].next=p;			
	}
	fclose(fp);
}



void showgraph(GH *G)
{
	int i;
	AR *p;
	for(i=0;i<G->vexnum;i++)
	{
		printf("%s ",G->vexname[i]);
		p=G->N[i].next;
		while(p)
		{
			printf("--%s ",G->vexname[p->index]);
			p=p->next;
						
		}
		printf("\n");
	}
	printf("\n");
}



//////////////////////////////////////////////////////////////////////////////
//
//  请完成下列函数，
//  (1)、判断图是否强连通，是返回1，否则返回0
//
//  (2)、输出所有与指定顶点start距离最远的顶点名（不包括那些与start不连通的顶点）
//  
//
////////////////////////////////////////////////////////////////////////////////

void DFS(GH *G , AR *x , int end , int *visit , int &ans)
{
	int pos = x->index;
	if(pos == end)
	{
		ans = 1;
		return;
	}
	auto *p = G->N[pos].next;
	while(p != nullptr)
	{
		if(!visit[p->index])
		{
			visit[p->index] = 1;
			DFS(G , p , end , visit , ans);
			visit[p->index] = 0;
		}
		if(ans)return;
		p = p->next;
	}
}

int isconect(GH *G)//判断图是否强连通，是返回1，否则返回0
{
	for(int i = 0;i < G->vexnum;i ++)
	{
		for(int j = i + 1;j < G->vexnum;j ++)
		{
			auto *p = G->N[i].next;
			while(p != nullptr)
			{
				int visit[10010] = {};
				visit[i] = 1;
				int ans = 0;
				if(!visit[p->index])
				{
					visit[p->index] = 1;
					DFS(G , p , j , visit , ans);
					visit[p->index] = 0;
				}
				if(!ans)return 0;
				p = p->next;
			}
			p = G->N[j].next;
			while(p != nullptr)
			{
				int visit[10010] = {};
				visit[j] = 1;
				int ans = 0;
				if(!visit[p->index])
				{
					visit[p->index] = 1;
					DFS(G , p , i , visit , ans);
					visit[p->index] = 0;
				}
				if(!ans)return 0;
				p = p->next;
			}
		}
	}
	return 1;
	/*int time[10010] = {};
	for(int i = 0;i < G->vexnum;i ++)
	{
		auto *p = G->N[i].next;
		while(p != nullptr)
		{
			time[p->index] ++;
			p = p->next;
		}
	}
	for(int i = 0;i < G->vexnum;i ++)
		if(time[i] == 0)return 0;
	return 1;*/
}

void dfs(GH *G , AR *x , int *visit , int *count , int time)
{
	int pos = x->index;
	if(count[pos] < time)count[pos] = time;
	auto *p = G->N[pos].next;
	while(p != nullptr)
	{
		if(!visit[p->index])
		{
			visit[p->index] = 1;
			dfs(G , p , visit , count , time + 1);
			visit[p->index] = 0;
		}
		p = p->next;
	}
}

void findfar(GH *G,char *start)//输出所有距离start最远的顶点
{
	int count[10010] = {};
	int visit[10010] = {};
	int max = 0;
	int pos = 0;
	while(strcmp(G->vexname[pos] , start) != 0)pos ++;
	visit[pos] = 1;
	auto *p = G->N[pos].next;
	while(p != nullptr)
	{
		if(!visit[p->index])
		{
			visit[p->index] = 1;
			dfs(G , p , visit , count , 1);
			visit[p->index] = 0;
		}
		p = p->next;
	}
	for(int i = 0;i < G->vexnum;i ++)if(count[i] > max)max = count[i];
	for(int i = 0;i < G->vexnum;i ++)
	{
		if(count[i] == max)cout << G->vexname[i] << ' ';
	}
	cout << endl;
}




