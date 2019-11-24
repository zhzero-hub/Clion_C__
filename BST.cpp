///////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ�󣺴���ƽ��Ķ����������BST��
//          1��������ϵͳ������ɣ�
//          2��ÿ����һ���ڵ�󣬼��ж�BST�Ƿ���ò�ƽ�⣬�����ڲ�ƽ�⣬�������������������������һ���ڵ�;
//          3��������ɺ󣬽����ɵ�BST��ʾ����
//          
////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctime>
#define N 15
using namespace std;

typedef struct node
{
	int data = 0;
	int ban = 0;//ƽ�����ӣ����Ҹ߶����Ϊ0������߸�Ϊ-1�����ұ߸�Ϊ1
	int h = 0;
	struct node *left = nullptr , *right = nullptr , *pa = nullptr;//���������ֱ�ָ�����Һ����븸�ڵ�
}BST;

BST *createbst(int n);//����BST
BST *insnode(BST *T,int x);//��TΪ���ڵ��BST�в������ݵ�x,������ж����Ƿ�ƽ�⣬���ƽ�⣬���β���ڵ���̽��������ظ��ڵ㣻
                           //������е�����������󷵻ظ��ڵ�
BST *delbst(BST *T);//����BST

void showbst(BST *T);//��ʾBST


BST *adjust(BST *T,BST *a,BST *b,BST *c);//��BST����������a�Ǵ������ڵ㿪ʼ���ϲ��ҵ��ĵ�һ����ƽ��Ľڵ�
                                         //b���ڲ���·����a�ĺ���,c���ڲ���·����b�ĺ���



int heightbst(BST *T);//�������ĸ߶�


int isbalance(BST *T,BST *newnode,BST **a,BST **b,BST **c);//����һ���ڵ���ж����Ƿ�ƽ�⣬�ǵĻ�����1�����򷵻�0.
                                                        //T�ǵ�ǰBST�ĸ��ڵ㣬newnode���²���Ľڵ�                                                        
                                                        //*a��ʾ�������ڵ㿪ʼ���ϲ��ҵ��ĵ�һ����ƽ��Ľڵ�
                                                        //*b���ڲ���·����*a�ĺ���
                                                        //*c���ڲ���·����*b�ĺ���
                                                        //���²���Ľڵ㿪ʼ�����϶���Ӧ�ڵ��ƽ������������


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	int n;
	BST *T=NULL;
	printf("���������ݹ�ģ:\n");
	scanf("%d",&n);
	while(n>0)
	{
		printf("������ƽ��BSTΪ��\n");
		T=createbst(n);
		showbst(T);
		T=delbst(T);
		printf("\n\n���������ݹ�ģ:\n");
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


BST *insnode(BST *T,int x)//����
{
//////////////����ϸ�Ķ��öδ��룬������ζ�isbanlance��adjust��������������////////////////////////////

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
	p->left=p->right=NULL;//����һ���½�㣬���Խ��ĸ�����Ա��ֵ
	if(!pa)//���������Ǹ��ڵ㣬�������������
		return p;
	else if(pa->data<x)//����²���Ĳ��Ǹ��ڵ㣬���ý�����丸�ڵ�������
		pa->right=p;
	else
		pa->left=p;
	if(isbalance(T,p,&a,&b,&c))//�����½��p���ж�BST�Ƿ�ƽ��
		return T;//���ƽ�⣬���β�����������ظ��ڵ�
	else
		return adjust(T,a,b,c);//�����ƽ�⣬��BST��������Ȼ�󷵻ظ��ڵ�
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
        if(p->ban < -1)//���
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
        else if(p->ban > 1)//�Ҹ�
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

int heightbst(BST *T)//����BST�߶�
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

void showbst(BST *T)//��ʾBST
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




BST *delbst(BST *T)//����BST
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