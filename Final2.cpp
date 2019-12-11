/////////////////////////////////////////////////////////////////////////////////////////
//
//              姓名：
//              
//              学号：
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

typedef struct node//定义树的节点结构
{
	int data;
	struct node *left,*right;
}BST;

BST *createbst(int n);//根据n个随机数创建BST，返回创建的BST的根节点
BST *insertnode(BST *T,int data);//在BST中插入一个数据节点，并返回BST的根节点
void showbst(BST *T);//显示树
int isbanlance(BST *T);//判断BST是否平衡，是返回1，否则返回0
float asl(BST *T);//计算并返回该BST查找不成功的ASL
void getleaflist(BST *T,BST *head);//将BST中所有的叶节点按照从左到右的顺序连接成一个双向链表,head为其头结点
void showleaflist(BST *head);//显示由BST的所有叶结点构成的双向链表
BST *delbst(BST *T,BST *head);//销毁BST(首先要恢复BST，然后调用DelBst函数做销毁)
BST *DelBst(BST *T);//



int main()
{
	BST *T=NULL,*head;
	int n;
	head=(BST *)malloc(sizeof(BST));//以head作为由叶节点连成的双向链表的头结点
	head->left=head->right=NULL;	
	printf("\n请输入数据规模:\n");
	cin >> n;
	while(n>0)		
	{
		T=createbst(n);//根据随机数创建BST
		showbst(T);//显示该BST
		printf("\n");
		printf("\n树的查找不成功的ASL=%.2f\n",asl(T));//计算该BST查找不成功的ASL
		if(isbanlance(T))//判断BST是否平衡
			printf("\n该BST是平衡的\n");
		else
			printf("\n该BST不平衡\n");
		printf("\n叶子节点组成的链表：\n");
		getleaflist(T,head);//将BST的所有叶结点按照从左到右的顺序连成一个双向链表，头结点是head		
		showleaflist(head);//显示该叶子节点连成的双向链表
		T=delbst(T,head);//销毁BST
		printf("\n请输入数据规模:\n");
	    cin >> n;
	}		
}


BST *createbst(int n)//根据n个随机数创建BST，并返回根节点
{
	BST *T=NULL;
	int i,x;
	srand(time(0));
	for(i=1;i<=n;i++)
	{
		x=rand()%100;//生成的数据都在100以内，是为了方便调试，不能以此作为条件设计算法
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
void showbst(BST *T)//显示树
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
BST *delbst(BST *T,BST *head)//先将BST的叶子节点复原，然后调用DelBst函数销毁BST
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

void showleaflist(BST *head)//显示叶子节点组成的链表的数据，正向输出一遍，再反向输出一遍
{
	BST *p;
	for(p=head->right;p!=head;p=p->right)
		printf("%d ",p->data);
	printf("\n");
	for(p=head->left;p!=head;p=p->left)
		printf("%d ",p->data);
	printf("\n");
	
}


////////////////////////////////完成下列函数////////////////////////////////////////////
////////////////////////////////完成下列函数////////////////////////////////////////////




float asl(BST *T)//计算并返回BST查找不成功的ASL
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


void getleaflist(BST *T,BST *head)//利用叶结点的左右指针将叶子节点连成一个双向循环链表，表头是head
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

int isbanlance(BST *T)//判断BST是否平衡，是返回1，否则返回0
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


