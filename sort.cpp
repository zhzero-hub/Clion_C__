/////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//        1����Ƹ�Ч�㷨ʵ�ֻ�������Ҫ��ռ临�Ӷ�O(c)��Ҫ��ֻ���ô���0��1������Ͱ��
//
//        
//        2����Ƹ�Ч�ǵݹ��㷨ʵ�ֹ鲢����
//        
//        3������ʽ�����ݽṹ����Ƹ�Ч�㷨ʵ��ð������ʹ����������Ҫ��ռ临�Ӷ�O(c)
//
//        4����Ҫ�޸��Ѹ����Ĺ������룬�����������ӺͶ�����Ҫ�Ĺ��ܺ��������ɵ��ÿ⺯��
//
//////////////////////////////////////////////////////////////////////////////////////




#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
typedef struct node
{
	int data;
	struct node *next;
}LI;//���������������ʽ�ṹ

void getdata(LI *A,LI *B,int *a,int n);//��ȡn������������������������һ������
void showlist(LI *head);//��ʾ��������
void showarray(int *a,int n);//��ʾ��������
void mergesort(int *a,int n);//�鲢����
void radixsort(LI *head);//��������
void bubblesort(LI *head);//ð������
void dellist(LI *head);//��������


main()
{
	int *a,n;
	LI *A,*B;
	A=(LI *)malloc(sizeof(LI));
	B=(LI *)malloc(sizeof(LI));
	A->next=B->next=NULL;//���������յĴ�ͷ����
	printf("\n���������ݹ�ģ:\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc((n+1)*sizeof(int));//0��λ�ò�������
		getdata(A,B,a,n);//��ȡ��������������
		radixsort(A);//��������
		mergesort(a,n);//�鲢����
		bubblesort(B);//ð������
		free(a);//�ͷ�����ռ�
		dellist(A);//��������
		dellist(B);//��������
		printf("\n���������ݹ�ģ:\n");//����������Ҫ��������ݹ�ģ
	    scanf("%d",&n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A,LI *B,int *a,int n)//��ȡn�������������������������
{
	LI *p;
	int i,x;
	srand(time(0));
	for(i=1;i<=n;i++)
	{
		x=rand();
		p=(LI *)malloc(sizeof(LI));
		p->data=x;
		p->next=A->next;
		A->next=p;
		p=(LI *)malloc(sizeof(LI));
		p->data=x;
		p->next=B->next;
		B->next=p;
		a[n-i+1]=x;//ע���������ЧԪ���Ǵ�a[1]----a[n]
	}	
}



void showlist(LI *head)//��ʾ��������
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

void showarray(int *a,int n)//��ʾ��������
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

void dellist(LI *head)//��������
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




void mergesort(int *a,int n)//�鲢����
{
	int *t;
	t=(int *)malloc((n+1)*sizeof(int));//��������
	
////////////////////////��ɸú���////////////////////////////////
	




////////////////////////��ɸú���////////////////////////////////
	printf("\n�鲢����Ľ����\n");
	showarray(a,n);
	free(t);
}



void bubblesort(LI *head)//ð������
{
////////////////////////��ɸú���////////////////////////////////
	



////////////////////////��ɸú���////////////////////////////////
	printf("\nð������Ľ����\n");
	showlist(head);
}





void radixsort(LI *head)//��������
{
////////////////////////��ɸú���////////////////////////////////
	



////////////////////////��ɸú���////////////////////////////////
	printf("\n��������Ľ����\n");
	showlist(head);
}




