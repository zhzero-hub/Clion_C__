/////////////////////////////////////////////////////////////////////////////////////////
//
//              ������֣��
//              
//              ѧ�ţ�161820217
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
using namespace std;

typedef struct arc//�ڽӱ�Ľ��ṹ
{
	int index;
	struct arc *next;
}AR;

typedef struct MyGraph//����ͼ�Ľṹ
{
	int type;//
	int vexnum;//�������
	char **vexname;//��Ŷ��������
	AR *N;//�ڽӱ�
}GH;



int findvex(char *s,GH *G);//ȷ�������Ӧ��ţ�������ŷ���
void creatgraph(GH *G);//�������ڽӾ����ʾ��ͼ
void showgraph(GH *G);//��ʾͼ
int isconect(GH *G);//�ж�ͼ�Ƿ�ǿ��ͨ���Ƿ���1�����򷵻�0
void findfar(GH *G,char *start);//�ҳ����о���start��Զ�Ķ���



int main()
{
	char s[100];
	GH G;//����ͼ�ı���
	creatgraph(&G);//����ͼ
	showgraph(&G);//��ʾͼ
	if(isconect(&G))
		printf("\n��ͼ��ǿ��ͨ��\n");
	else
		printf("\n��ͼ����ǿ��ͨ��\n");
	printf("\n�����붥����:\n");
	cin >> s;//s��ʾһ��������������findfar������������붥��s������Զ�Ķ���������������s����ͨ�Ķ��㣩
	while(strcmp(s,"#")!=0)
	{
		findfar(&G,s);
		printf("\n�����붥����:\n");
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
		printf("�޷���ͼ�������ļ�\n");
		exit(-1);
	}
	fscanf(fp,"%d",&M);
	G->vexnum=M;
	G->type=1;//����ͼ
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
//  ��������к�����
//  (1)���ж�ͼ�Ƿ�ǿ��ͨ���Ƿ���1�����򷵻�0
//
//  (2)�����������ָ������start������Զ�Ķ���������������Щ��start����ͨ�Ķ��㣩
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

int isconect(GH *G)//�ж�ͼ�Ƿ�ǿ��ͨ���Ƿ���1�����򷵻�0
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

void findfar(GH *G,char *start)//������о���start��Զ�Ķ���
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




