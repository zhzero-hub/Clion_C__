///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӾ��󴴽���������
//2�����жϸ��������Ƿ���ͨ���Ƿ������·������ʱ�临�Ӷȣ�
//3�����������������֮������м�·�����Լ����Ե�·�����ȣ�·������ָ����·�������бߵ�Ȩֵ֮�ͣ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int maxx = 9999999;//����������ֵ

typedef struct MyGraph
{
    int type;//0����ʾ��������1��ʾ������
    int arcnum = 0,vexnum = 0;//ͼ�бߵĸ����Լ��������
    char vexname[20][20];//��Ŷ������Ķ�ά����
    int A[20][20];//�ڽӾ���A[i][j]��ʾi�Ŷ�����j�Ŷ���֮��ߵ�Ȩֵ����i,j֮��û�бߣ���A[i][j]ȡֵ�����
}GH;
int menu_select();
int findvex(char *s,GH *G);//ȷ������s��Ӧ�����
void creatgraph(GH *G);//���ڽӾ������ʽ����ͼ
void showgraph(GH *G);//���ڽӱ����ʽ��ʾͼ
void findpath(GH *G,char *start,char *end);//Ѱ�Ҽ�·��
int iscycle(GH *G);//�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
int isconnect(GH *G);//�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0

int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.�������������ڽӾ���\n");
        printf("2.�ж��������Ƿ���ͨ\n");
        printf("3.�ж����������Ƿ��л�·\n");
        printf("4.���������������֮������м�·���Լ�·������\n");
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
                    printf("\n��ͼ����ͨ��\n");
                else
                    printf("\n��ͼ������ͨ��\n");
                system("pause");
                break;
            case 3:
                showgraph(&G);
                if(iscycle(&G))
                    printf("\n��ͼ�а�����·\n");
                else
                    printf("\n��ͼ�в�������·\n");
                system("pause");
                break;
            case 4:
                showgraph(&G);
                printf("\n��������ֹ����������:\n");
                scanf("%s%s",c1,c2);
                printf("���д� %s �� %s �ļ�·���Լ�·�����ȣ�\n",c1,c2);
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
        cout << "�ļ���ʧ��" << endl;
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

void findpath(GH *G,char *start,char *end)//Ѱ�Ҽ�·������
{
    int pos = findvex(start , G);
    int visit[20] = {};
    visit[pos] = 1;
    vector<char *>path;
    path.push_back(start);
    Find(G , end , pos , visit , path);
}


int iscycle(GH *G)//�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
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


int isconnect(GH *G)//�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0
{
///////////////////////////��ɸú���////////////////////////////////


}





