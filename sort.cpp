/////////////////////////////////////////////////////////////////////////////////////
//??????
//        1??????完????????????????還???O(c)?????????????0??1?????????
//
//        
//        2??????完?????????攢????
//        
//        3????????????????????完???????????????????????????還???O(c)
//
//        4?????????????????????????????????????????????????????????????
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
}LI;//??????????????????

void getdata(LI *A,LI *B,int *a,int n);//???n???????????????????????????????
void showlist(LI *head);//???????????
void showarray(int *a,int n);//???????????
void mergesort(int *a,int n);//?攢????
void radixsort(LI *head);//????????
void bubblesort(LI *head);//???????
void dellist(LI *head);//????????


int main()
{
	int *a,n;
	LI *A,*B;
	A=(LI *)malloc(sizeof(LI));
	B=(LI *)malloc(sizeof(LI));
	A->next=B->next=nullptr;//?????????????????
	printf("\n????????????:\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc((n+1)*sizeof(int));//0??竹?辰???????
		getdata(A,B,a,n);//?????????????????
		radixsort(A);//????????
		mergesort(a,n);//?攢????
		bubblesort(B);//???????
		free(a);//?????????
		dellist(A);//????????
		dellist(B);//????????
		printf("\n????????????:\n");//??????????????????????
	    scanf("%d",&n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A,LI *B,int *a,int n)//???n?????????????????????????
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
		a[n-i+1]=x;//??????????完??????a[1]----a[n]
	}	
}



void showlist(LI *head)//???????????
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

void showarray(int *a,int n)//???????????
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

void dellist(LI *head)//????????
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

void mergesort(int *a,int n)//?攢????
{
    cout << endl;
	int *t;
	t=(int *)malloc((n+1)*sizeof(int));//????????
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
	printf("\n?攢?????????\n");
	showarray(a,n);
	free(t);
}



void bubblesort(LI *head)//???????
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
	printf("\n????????????\n");
	showlist(head);
}





void radixsort(LI *head)//????????
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
    int size = 0;//????????size竹
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
	printf("\n?????????????\n");
	showlist(head);
	
}




