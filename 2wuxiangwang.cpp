///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӾ��󴴽���������
//2�����жϸ��������Ƿ���ͨ���Ƿ������·������ʱ�临�Ӷȣ�
//3�����������������֮������м�·�����Լ����Ե�·�����ȣ�·������ָ����·�������бߵ�Ȩֵ֮�ͣ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define maxx 9999999//����������ֵ

typedef struct MyGraph
{
    int type;//0����ʾ��������1��ʾ������
    int arcnum,vexnum;//ͼ�бߵĸ����Լ��������
    char **vexname;//��Ŷ������Ķ�ά����
    int **A;//�ڽӾ���A[i][j]��ʾi�Ŷ�����j�Ŷ���֮��ߵ�Ȩֵ����i,j֮��û�бߣ���A[i][j]ȡֵ�����
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
    printf("read file erro\n");
    exit(-1);
}

void creatgraph(GH *G)
{
///////////////////////////��ɸú���////////////////////////////////
    char filename[]="graph2.txt";


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





void findpath(GH *G,char *start,char *end)//Ѱ�Ҽ�·������
{
///////////////////////////��ɸú���////////////////////////////////



}


int iscycle(GH *G)//�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
{
///////////////////////////��ɸú���////////////////////////////////


}


int isconnect(GH *G)//�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0
{
///////////////////////////��ɸú���////////////////////////////////


}





