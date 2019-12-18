//******************************************************************
//*章节：第三次上机题第五题
//*题目：输出包括 M 行,每一行表示一次鼠标点击的结果。如果该次鼠
//*		标点击选择了一个窗口,则输出这个窗口的编号(窗口按照输入
//*		中的顺序从 1 编号到 N);如果没有,则输出"IGNORED"(不含双引号)。
//*作者：范文鑫
//*日期：2019年10月19
//********************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef  int Status;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLKE -1
#define OVERFLOW -2

typedef struct ElemType
{
    int x1,x2;
    int y1,y2;
    int num;
    ElemType(){;};
};

typedef struct
{
    int x;
    int y;
}Click;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

//初始化一个线性表
Status InitList_L(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    if(!L)
        exit(OVERFLOW);
    L->data.x1 = 0;
    L->data.x2 = 0;
    L->data.y1 = 0;
    L->data.y2 = 0;
    L->next = NULL;
    return OK;
}

//销毁一个线性表
Status DestrotList_L(LinkList &L)
{
    LNode *p = L;

    if(!L)
        return ERROR;

    while(p)
    {
        p = L->next;
        free(L);
        L = p;
    }
    return OK;
}

//清空一个线性表
Status ClearList_L(LinkList &L)
{
    LinkList p = NULL, pre = NULL;

    if(!L)
        return ERROR;

    pre = L->next;
    while(pre)
    {
        p = pre->next;
        free(pre);
        pre = p;
    }
    return OK;
}

//判空线性表
Status ListEmpty_L(LinkList L)
{
    if(L&&L->next == NULL)
        return TRUE;
    else
        return FALSE;
}

//用e返回线性表中第i个元素的值
Status GetElem_L(LinkList L, int i, ElemType &e)
{
    LinkList p = NULL;
    int j = 1;

    p = L->next;
    while(p&&j < i)
    {
        p = p->next;
        ++j;
    }
    if(!p||j > i)
        return ERROR;
    e = p->data;
    return OK;
}

//在L第i个位置前插入新的数据元素e
Status ListInsert_L(LinkList &L,int i, ElemType e)
{
    LinkList p = NULL, s = NULL;
    int j = 0;

    p = L;

    while(p&&j<i-1)
    {
        p = p->next;
        j++;
    }
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//删除线性表L的第i个元素，用e返回其值
Status ListDelete_L(LinkList &L, int i, ElemType &e)
{
    LinkList p = NULL, q = NULL;
    int j = 1;
    q = L;
    p = L->next;
    while(p->next&&j <= i)
    {
        q = q->next;
        p = p->next;
        j++;
    }
    q->next = p->next;
    e = p->data;
    free(p);
    p = NULL;
    return OK;
}

Status MoveWindow(LinkList L, int N, int M)
{
    ElemType n[81], e;
    Click m[81];
    LinkList p = NULL;
    int flag = 0;

    for(int i = 0; i < N; i++)
    {
        scanf("%d %d %d %d", &n[i].x1, &n[i].y1, &n[i].x2, &n[i].y2);
        n[i].num = i + 1;
        ListInsert_L(L, 1, n[i]);
    }
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d", &m[i].x, &m[i].y);
    }

    for(int i = 0; i < M; i++)
    {	p = L->next;

        while(p)
        {
//			printf("%d,%d,%d,%d\n",p->data.x1,p->data.x2,p->data.y1,p->data.y2);
//			printf("mx = %d, my = %d\n", m[i].x,m[i].y);
            if((p->data.x1<= m[i].x)&&(m[i].x <= p->data.x2)&&(p->data.y1 <= m[i].y)&&(m[i].y <= p->data.y2))
            {
                flag = 1;
                ListDelete_L(L, i + 1, e);
                ListInsert_L(L, 1, e);
                break;
            }
            p = p->next;
        }
        if(flag == 1)
        {
            printf("%d\n", e.num);
        }
        else printf("IGNORED\n");
    }
    return OK;
}

int main()
{
    int N = 0, M = 0;
    LinkList L;
    InitList_L(L);

    printf("请输入N的值：");
    scanf("%d", &N);
    printf("请输入M的值: ");
    scanf("%d", &M);

    MoveWindow(L, N, M);
    return 0;
}
