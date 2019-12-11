/////////////////////////////////////////////////////////////////////////////////////////
//
//              ������
//              
//              ѧ�ţ�
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include <iostream>
using namespace std;
#define N 100

typedef struct node//�������Ľڵ�ṹ
{
	int data;
	struct node *left,*right;
}BST;

BST *createbst(int n);//����n�����������BST�����ش�����BST�ĸ��ڵ�
BST *insertnode(BST *T,int data);//��BST�в���һ�����ݽڵ㣬������BST�ĸ��ڵ�
void showbst(BST *T);//��ʾ��
int isbanlance(BST *T);//�ж�BST�Ƿ�ƽ�⣬�Ƿ���1�����򷵻�0
float asl(BST *T);//���㲢���ظ�BST���Ҳ��ɹ���ASL
void getleaflist(BST *T,BST *head);//��BST�����е�Ҷ�ڵ㰴�մ����ҵ�˳�����ӳ�һ��˫������,headΪ��ͷ���
void showleaflist(BST *head);//��ʾ��BST������Ҷ��㹹�ɵ�˫������
BST *delbst(BST *T,BST *head);//����BST(����Ҫ�ָ�BST��Ȼ�����DelBst����������)
BST *DelBst(BST *T);//



int main()
{
	BST *T=NULL,*head;
	int n;
	head=(BST *)malloc(sizeof(BST));//��head��Ϊ��Ҷ�ڵ����ɵ�˫�������ͷ���
	head->left=head->right=NULL;	
	printf("\n���������ݹ�ģ:\n");
	cin >> n;
	while(n>0)		
	{
		T=createbst(n);//�������������BST
		showbst(T);//��ʾ��BST
		printf("\n");
		printf("\n���Ĳ��Ҳ��ɹ���ASL=%.2f\n",asl(T));//�����BST���Ҳ��ɹ���ASL
		if(isbanlance(T))//�ж�BST�Ƿ�ƽ��
			printf("\n��BST��ƽ���\n");
		else
			printf("\n��BST��ƽ��\n");
		printf("\nҶ�ӽڵ���ɵ�����\n");
		getleaflist(T,head);//��BST������Ҷ��㰴�մ����ҵ�˳������һ��˫������ͷ�����head		
		showleaflist(head);//��ʾ��Ҷ�ӽڵ����ɵ�˫������
		T=delbst(T,head);//����BST
		printf("\n���������ݹ�ģ:\n");
	    cin >> n;
	}		
}


BST *createbst(int n)//����n�����������BST�������ظ��ڵ�
{
	BST *T=NULL;
	int i,x;
	srand(time(0));
	for(i=1;i<=n;i++)
	{
		x=rand()%100;//���ɵ����ݶ���100���ڣ���Ϊ�˷�����ԣ������Դ���Ϊ��������㷨
		T=insertnode(T,x);
	}
	return T;	
}

BST *insertnode(BST *T,int data)
{
	if(!T)
	{
		T=(BST *)malloc(sizeof(BST));
		T->left=T->right=NULL;
		T->data=data;
		return T;
	}
	else if(T->data==data)
		return T;
	else if(T->data<data)
		T->right=insertnode(T->right,data);
	else
		T->left=insertnode(T->left,data);
	return T;
}
void showbst(BST *T)//��ʾ��
{
	if(T)
	{
		printf("%d",T->data);
		if(T->left||T->right)
		{
			printf("(");
			showbst(T->left);
			printf(",");
			showbst(T->right);
			printf(")");
		}
	}
}
BST *delbst(BST *T,BST *head)//�Ƚ�BST��Ҷ�ӽڵ㸴ԭ��Ȼ�����DelBst��������BST
{
	BST *p,*p2;
	p=head->right;
	while(p!=head)
	{
		p2=p->right;
		p->left=p->right=NULL;
		p=p2;
	}
	head->left=head->right=NULL;
	T=DelBst(T);
	return NULL;
}

BST *DelBst(BST *T)
{
	if(T)
	{
		T->left=DelBst(T->left);
		T->right=DelBst(T->right);
		free(T);
		return NULL;
	}
	else
		return NULL;
}

void showleaflist(BST *head)//��ʾҶ�ӽڵ���ɵ���������ݣ��������һ�飬�ٷ������һ��
{
	BST *p;
	for(p=head->right;p!=head;p=p->right)
		printf("%d ",p->data);
	printf("\n");
	for(p=head->left;p!=head;p=p->left)
		printf("%d ",p->data);
	printf("\n");
	
}


////////////////////////////////������к���////////////////////////////////////////////
////////////////////////////////������к���////////////////////////////////////////////




float asl(BST *T)//���㲢����BST���Ҳ��ɹ���ASL
{
	node *stack[10010] = {};
	int time[10010] = {};
	int top = 0;
	int num = 0;
	float sum = 0;
	time[top] = 0;
	stack[top ++] = T;
	while(top > 0)
	{
		int t = time[top - 1];
		node *p = stack[-- top];
		if(p->left == nullptr && p->right == nullptr)
		{
			sum += t + 1;
			num ++;
			continue;
		}
		if(p->right != nullptr)
		{
			time[top] = t + 1;
			stack[top ++] = p->right;
		}
		else
		{
			sum += t + 1;
			num ++;
		}
		if(p->left != nullptr)
		{
			time[top] = t + 1;
			stack[top ++] = p->left;
		}
		else
		{
			sum += t + 1;
			num ++;
		}
	}
	return sum / float(num);
}


void getleaflist(BST *T,BST *head)//����Ҷ��������ָ�뽫Ҷ�ӽڵ�����һ��˫��ѭ��������ͷ��head
{
	node *pos = head;
	node *stack[10010] = {};
	int top = 0;
	stack[top ++] = T;
	node *end;
	while(top > 0)
	{
		node *p = stack[-- top];
		if(p->left == nullptr && p->right == nullptr)
		{
			end = p;
			pos->right = end;
			end->left = pos;
			pos = pos->right;
			continue;
		}
		if(p->right != nullptr)
		{
			stack[top ++] = p->right;
		}
		if(p->left != nullptr)
		{
			stack[top ++] = p->left;
		}
	}
	end->right = head;
	head->left = end;
}

int isbanlance(BST *T)//�ж�BST�Ƿ�ƽ�⣬�Ƿ���1�����򷵻�0
{
	if(T == nullptr)return 1;
	node *queue[10010] = {};
	int flag = 0;
	int l = 0;
	int r = 0;
	queue[r ++] = T;
	while(l < r)
	{
		for(int i = l;i < r;i ++)
		{
			if(queue[i] == nullptr)
			{
				flag = 1;
				break;
			}
		}
		node *p = queue[l ++];
		if(p == nullptr)continue;
		if(flag)
		{
			if(p->left != nullptr || p->right != nullptr)return 0;
		}
		queue[r ++] = p->left;
		queue[r ++] = p->right;
	}
	return 1;
}


