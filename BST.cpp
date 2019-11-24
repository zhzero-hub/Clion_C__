///////////////////////////////////////////////////////////////////////////////////////////
//题目要求：创建平衡的二叉查找树（BST）
//          1、数据由系统随机生成；
//          2、每插入一个节点后，即判断BST是否会变得不平衡，若存在不平衡，则做出调整；否则继续插入下一个节点;
//          3、创建完成后，将建成的BST显示出来
//          
////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctime>
#define N 15
using namespace std;

typedef struct node
{
	int data = 0;
	int ban = 0;//平衡因子，左右高度相等为0；若左边高为-1；若右边高为1
	int h = 0;
	struct node *left = nullptr , *right = nullptr , *pa = nullptr;//三叉链，分别指向左右孩子与父节点
}BST;

BST *createbst(int n);//创建BST
BST *insnode(BST *T,int x);//在T为根节点的BST中插入数据点x,插入后判断树是否平衡，如果平衡，本次插入节点过程结束，返回根节点；
                           //否则进行调整，调整完后返回根节点
BST *delbst(BST *T);//销毁BST

void showbst(BST *T);//显示BST


BST *adjust(BST *T,BST *a,BST *b,BST *c);//在BST中做调整，a是从新增节点开始向上查找到的第一个不平衡的节点
                                         //b是在查找路线上a的孩子,c是在查找路线上b的孩子



int heightbst(BST *T);//计算树的高度


int isbalance(BST *T,BST *newnode,BST **a,BST **b,BST **c);//新增一个节点后，判断树是否平衡，是的话返回1，否则返回0.
                                                        //T是当前BST的根节点，newnode是新插入的节点                                                        
                                                        //*a表示从新增节点开始向上查找到的第一个不平衡的节点
                                                        //*b是在查找路线上*a的孩子
                                                        //*c是在查找路线上*b的孩子
                                                        //从新插入的节点开始，向上对相应节点的平衡因子做更新


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	int n;
	BST *T=NULL;
	printf("请输入数据规模:\n");
	scanf("%d",&n);
	while(n>0)
	{
		printf("创建的平衡BST为：\n");
		T=createbst(n);
		showbst(T);
		T=delbst(T);
		printf("\n\n请输入数据规模:\n");
	    scanf("%d",&n);
	}	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BST *createbst(int n)
{
	int i,x;
	BST *T=NULL;
	srand(time(0));
	for(i=0;i<n;i++)
	{
	    x = rand() % 1000;
		T=insnode(T,x);
	}
	return T;
}


BST *insnode(BST *T,int x)//插入
{
//////////////请仔细阅读该段代码，看其如何对isbanlance和adjust两个函数做调用////////////////////////////

	BST *p=T,*pa=NULL;
	BST *a,*b,*c;
	while(p)
	{
		if(p->data==x)
			return T;
		else if(p->data<x)
		{
			pa=p;
			p=p->right;
		}
		else
		{
			pa=p;
			p=p->left;
		}
	}
	p=(BST *)malloc(sizeof(BST));
	p->ban=0;
	p->data=x;
	p->pa=pa;
	p->left=p->right=NULL;//创建一个新结点，并对结点的各个成员赋值
	if(!pa)//如果插入的是根节点，插入结束，返回
		return p;
	else if(pa->data<x)//如果新插入的不是根节点，将该结点与其父节点连起来
		pa->right=p;
	else
		pa->left=p;
	if(isbalance(T,p,&a,&b,&c))//插入新结点p后，判断BST是否平衡
		return T;//如果平衡，本次插入结束，返回根节点
	else
		return adjust(T,a,b,c);//如果不平衡，对BST做调整，然后返回根节点
}

int max(int a , int b)
{
    if(a > b)return a;
    return b;
}

void Getban(node *x)
{
    if(x == nullptr)return;
    else x->ban = heightbst(x->right) - heightbst(x->left);
}

int isbalance(BST *T,BST *newnode,BST **a,BST **b,BST **c)
{
    node *p = newnode->pa;
    node *q = newnode;
    while(q != T)
    {
        Getban(p);
        if(p->ban < -1)//左高
        {
            if(newnode->data < q->data)//LL
            {
                *a = p;
                *b = q;
                *c = nullptr;
            }
            else//LR
            {
                *a = p;
                *b = q;
                *c = q->right;
            }
            return 0;
        }
        else if(p->ban > 1)//右高
        {
            if(newnode->data < q->data)//RL
            {
                *a = p;
                *b = q;
                *c = q->left;
            }
            else//RR
            {
                *a = p;
                *b = q;
                *c = nullptr;
            }
            return 0;
        }
        p = p->pa;
        q = q->pa;
    }
    return 1;
}

BST *LL_Rotation(BST *T,BST *a,BST *b,BST *c)
{
    int isRoot = 0;
    if(T == a)isRoot = 1;
    int dir = 0;
    node *temp_pa = a->pa;
    if(temp_pa != nullptr && temp_pa->right == a)dir = 1;
    node *p = b->right;
    b->right = a;
    a->pa = b;
    a->left = p;
    b->pa = temp_pa;
    if(temp_pa != nullptr)
    {
        if(dir)temp_pa->right = b;
        else temp_pa->left = b;
    }
    if(p != nullptr)p->pa = a;
    if(isRoot)T = b;
    return T;
}

BST *RR_Rotation(BST *T,BST *a,BST *b,BST *c)
{
    int isRoot = 0;
    if(T == a)isRoot = 1;
    int dir = 0;
    node *temp_pa = a->pa;
    if(temp_pa != nullptr && temp_pa->right == a)dir = 1;
    node *p = b->left;
    b->left = a;
    a->pa = b;
    a->right = p;
    b->pa = temp_pa;
    if(temp_pa != nullptr)
    {
        if(dir)temp_pa->right = b;
        else temp_pa->left = b;
    }
    if(p != nullptr)p->pa = a;
    if(isRoot)T = b;
    return T;
}

BST *adjust(BST *T,BST *a,BST *b,BST *c)
{
    if(c == nullptr)//LL||RR
    {
        if(a->left == b)//LL
        {
            T = LL_Rotation(T , a , b , c);
        }
        else//RR
        {
            T = RR_Rotation(T , a , b , c);
        }
    }
    else//LR||RL
    {
        if(b->right == c)//LR
        {
            T = RR_Rotation(T , b , c , a);
            T = LL_Rotation(T , a , c , b);
        }
        else//RL
        {
            T = LL_Rotation(T , b , c , a);
            T = RR_Rotation(T , a , c , b);
        }
    }
    return T;
}

int heightbst(BST *T)//计算BST高度
{
	int h1,h2;
	if(!T)
		return 0;
	else
	{
		h1=heightbst(T->left);
		h2=heightbst(T->right);
		if(h1>h2)
			return (h1+1);
		else
			return (h2+1);
	}
}

void showbst(BST *T)//显示BST
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




BST *delbst(BST *T)//销毁BST
{
	if(T == nullptr)
		return nullptr;
	else
	{
		T->left=delbst(T->left);
		T->right=delbst(T->right);
		free(T);
		T = nullptr;
		return nullptr;
	}
}