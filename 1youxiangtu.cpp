///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӱ�������ͼ��
//2����Ƶݹ��㷨Ѱ������ͨ��ָ���ڵ�ļ򵥻�·
//3������㷨�жϴӶ���u������v�Ƿ����·��������ʱ�临�Ӷȣ�
//4������㷨�������ж������ȣ�����ʱ�临�Ӷȣ�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct arcnode
{
    int index;//�ڽӵ����
    struct arcnode *next;
}AR;

typedef struct MyGraph
{
    int type;//0����ʾ����ͼ��1��ʾ����ͼ
    int arcnum,vexnum;//ͼ�бߵĸ����Լ��������
    char **vexname;//��Ŷ������Ķ�ά����
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
    printf("read file erro\n");
    exit(-1);
}

void creatgraph(GH *G)
{
////////////////////////��ɸú���///////////////////////////////////////////////
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


void findpath(GH *G,char *start)//Ѱ�����о�������start�ļ򵥻�·
{
////////////////////////��ɸú���///////////////////////////////////////////////


}

void indegree(GH *G)//���㲢��ʾ���ͼ��ÿ����������
{
////////////////////////��ɸú���///////////////////////////////////////////////

}

int ispath(GH *G,char *start,char *end)//�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
{
///////////////////////��ɸú���///////////////////////////////////////////////

}






