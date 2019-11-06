///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӱ�������ͼ��
//2����Ƶݹ��㷨Ѱ������ͨ��ָ���ڵ�ļ򵥻�·
//3������㷨�жϴӶ���u������v�Ƿ����·��������ʱ�临�Ӷȣ�
//4������㷨�������ж������ȣ�����ʱ�临�Ӷȣ�
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
    int index = -1;//�ڽӵ����
    struct arcnode *next = nullptr;
}AR;

typedef struct MyGraph
{
    int type = -1;//0����ʾ����ͼ��1��ʾ����ͼ
    int arcnum = 0,vexnum = 0;//ͼ�бߵĸ����Լ��������
    char *vexname[20];//��Ŷ������Ķ�ά����
    AR *N;//����ڽӱ�ͷ��������
}GH;

int findvex(char *s,GH *G);//ȷ������s��Ӧ�����
void creatgraph(GH *G);//���ڽӱ����ʽ����ͼ
void showgraph(GH *G);//���ڽӱ����ʽ��ʾͼ
void findpath(GH *G,char *start);//Ѱ�����о�������start�ļ�·��
int ispath(GH *G,char *start,char *end);//�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
void indegree(GH *G);//���㲢��ʾ���ͼ��ÿ����������
int menu_select();


int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.��������ͼ���ڽӱ�\n");
        printf("2.������о���ָ������ļ򵥻�·\n");
        printf("3.�ж���������֮���Ƿ����·��\n");
        printf("4.������ж�������\n");
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
                printf("�����붥����:\n");
                scanf("%s",c1);
                printf("���о���%s�ļ򵥻�·��:\n",c1);
                findpath(&G,c1);
                system("pause");
                break;
            case 3:
                showgraph(&G);
                printf("��������ֹ����������:\n");
                scanf("%s%s",c1,c2);
                if(ispath(&G,c1,c2))
                    printf("�Ӷ���%s������%s����·��\n",c1,c2);
                else
                    printf("�Ӷ���%s������%s������·��\n",c1,c2);
                system("pause");
                break;
            case 4:
                showgraph(&G);
                printf("\nͼ�����ж�������:\n");
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




int findvex(char *s,GH *G)//���ݶ�����ȷ���ö���ı��
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
        cout << "�ļ���ʧ��" << endl;
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


void findpath(GH *G,char *start)//Ѱ�����о�������start�ļ򵥻�·
{
    int visit[20] = {};
    vector<char *> path;
    int pos = findvex(start , G);
    visit[pos] = 1;
    path.push_back(start);
    AR *x = &G->N[pos];
    x = x->next;
    if(x == nullptr)cout << "�õ�Ϊ������" << endl;
    Find(G , start , x , visit , path);
}

void indegree(GH *G)//���㲢��ʾ���ͼ��ÿ����������
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
    for(int i = 0;i < G->vexnum;i ++)cout << G->vexname[i] << "�����Ϊ: " << ans[i] << endl;
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

int ispath(GH *G,char *start,char *end)//�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
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






