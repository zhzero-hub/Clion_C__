/////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//        1、设计高效算法实现基数排序，要求空间复杂度O(c)，要求只能用代表0和1的两个桶；
//
//        
//        2、设计高效非递归算法实现归并排序
//        
//        3、在链式的数据结构中设计高效算法实现冒泡排序，使得链表有序，要求空间复杂度O(c)
//
//        4、不要修改已给定的公共代码，可以自行增加和定义需要的功能函数，不可调用库函数
//
//////////////////////////////////////////////////////////////////////////////////////




#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}LI;//基数排序所需的链式结构

void getdata(LI *A,LI *B,int *a,int n);//获取n个随机数创建两个无序链表和一个数组
void showlist(LI *head);//显示链表数据
void showarray(int *a,int n);//显示数组数据
void mergesort(int *a,int n);//归并排序
void radixsort(LI *head);//基数排序
void bubblesort(LI *head);//冒泡排序
void dellist(LI *head);//销毁链表


int main()
{
	int *a,n;
	LI *A,*B;
	A=(LI *)malloc(sizeof(LI));
	B=(LI *)malloc(sizeof(LI));
	A->next=B->next=nullptr;//创建两个空的带头链表
	printf("\n请输入数据规模:\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc((n+1)*sizeof(int));//0号位置不放数据
		getdata(A,B,a,n);//获取链表与数组数据
		radixsort(A);//基数排序
		mergesort(a,n);//归并排序
		bubblesort(B);//冒泡排序
		free(a);//释放数组空间
		dellist(A);//销毁链表
		dellist(B);//销毁链表
		printf("\n请输入数据规模:\n");//重新输入需要排序的数据规模
	    scanf("%d",&n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A,LI *B,int *a,int n)//获取n个随机数创建无序链表与数组
{
	LI *p;
	int i,x;
	srand(time(0));
	for(i=1;i<=n;i++)
	{
		x=rand() % 100;
		p=(LI *)malloc(sizeof(LI));
		p->data=x;
		p->next=A->next;
		A->next=p;
		p=(LI *)malloc(sizeof(LI));
		p->data=x;
		p->next=B->next;
		B->next=p;
		a[n-i+1]=x;//注意数组的有效元素是从a[1]----a[n]
	}	
}



void showlist(LI *head)//显示链表内容
{
	int i=0;
	LI *p=head->next;
	while(p)
	{
		printf("%-6d ",p->data);
		i++;
		if(i%15==0)
			printf("\n");
		p=p->next;
	}
	printf("\n");
}

void showarray(int *a,int n)//显示数组内容
{
	int i,j;
	for(i=1,j=0;i<=n;i++)
	{
		printf("%-6d ",a[i]);
		j++;
		if(j%15==0)
			printf("\n");
	}
	printf("\n");
}

void dellist(LI *head)//销毁链表
{
	LI *p,*p2;
	p=head->next;
	head->next=NULL;
	while(p)
	{
		p2=p->next;
		free(p);
		p=p2;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Merge(int *a , int *t , int l , int r , int mid)
{
    if(l == r)return;
    else
    {
        int pos = l;
        int x = l;
        int y = mid + 1;
        while(x <= mid && y <= r)
        {
            if(a[x] < a[y])
            {
                t[pos] = a[x];
                x ++;
                pos ++;
            }
            else if(a[x] > a[y])
            {
                t[pos] = a[y];
                y ++;
                pos ++;
            }
            else
            {
                t[pos] = a[x];
                pos ++;
                t[pos] = a[y];
                pos ++;
                x ++;
                y ++;
            }
        }
        while(x <= mid)
        {
            t[pos] = a[x];
            pos ++;
            x ++;
        }
        while(y <= r)
        {
            t[pos] = a[y];
            pos ++;
            y ++;
        }
        for(int i = l;i <= r;i ++)a[i] = t[i];
    }
}

void mergesort(int *a,int n)//归并排序
{
    cout << endl;
	int *t;
	t=(int *)malloc((n+1)*sizeof(int));//辅助数组
    int len = 2;
    while(len < n)
    {
        int l = 1 , r = n;
        int pos = 1;
        while(pos < n)
        {
            pos = l + len - 1;
            if(pos > n)r = n;
            else r = pos;
            int mid = (l + r) / 2;
            if(a[mid + 1] < a[mid])Merge(a , t , l , r , mid);
            l = pos + 1;
        }
        len *= 2;
    }
    Merge(a , t , 1 , n , len / 2);
	printf("\n归并排序的结果：\n");
	showarray(a,n);
	free(t);
}



void bubblesort(LI *head)//冒泡排序
{
    LI *end = head->next;
    LI *f = head;
    while(end != nullptr)
    {
        f = f->next;
        end = end->next;
    }
    while(f != head)
    {
        LI *r = head->next;
        LI *l = head;
        while(r->next != end && r != end)
        {
            LI *p = r->next;
            if(p->data < r->data)
            {
                LI *temp = p->next;
                l->next = p;
                p->next = r;
                r->next = temp;
                l = l->next;
                continue;
            }
            l = l->next;
            r = r->next;
        }
        end = r;
        f = l;
    }
	printf("\n冒泡排序的结果：\n");
	showlist(head);
}





void radixsort(LI *head)//基数排序
{
    LI *x = (LI *)malloc(sizeof(LI));//0
    LI *y = (LI *)malloc(sizeof(LI));//1
    LI *x_pos = x;
    LI *y_pos = y;
    int max = 0;
    LI *p = head->next;
    while(p != nullptr)
    {
        if(max < p->data)max = p->data;
        p = p->next;
    }
    int size = 0;//最大的数有size位
    while(max > 0)
    {
        max /= 10;
        size ++;
    }
    for(int i = 0;i < size;i ++)
    {
        p = head->next;
        int t = p->data;
        t /= pow(10 , i);
        while(p != nullptr)
        {
            if(t % 2)
            {
                y_pos->next = p;
                y_pos = y_pos->next;
            }
            else
            {
                x_pos->next = p;
                x_pos = x_pos->next;
            }
            p = p->next;
        }
        x_pos = x->next;
        y_pos = y->next;
        p = head;
        while(x_pos != nullptr)
        {
            p->next = x_pos;
            p = p->next;
            x_pos = x_pos->next;
        }
        while(y_pos != nullptr)
        {
            p->next = y_pos;
            p = p->next;
            y_pos = y_pos->next;
        }
        p->next = nullptr;
    }
	printf("\n基数排序的结果：\n");
	showlist(head);

}




