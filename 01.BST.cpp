///////////////////////////////////////////////////////////////////////////////////////////
//题目要求：在BST中做处理
//          1、根据系统随机生成的数据创建BST；
//          2、计算该BST的平均查找长度ASL（等概率，查找成功的）；
//          3、在BST中做删除
//          
////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;
const int N = 100;

typedef struct node
{
	int data;
	struct node *left,*right;
}BST;

BST *createbst(int n);//创建BST
BST *insnode(BST *T,int x);//在BST中插入数据点x,并返回根节点指向
BST *delnode(BST *T,int x);//在BST中删除包含x的节点，并返回根节点指向
void showbst(BST *T);//显示BST
float comasl(BST *T);//计算并返回等概率查找下，该BST的平均查找长度
BST *delbst(BST *T);//销毁BST

int main()
{
	int i,n,x;
	BST *T=NULL;
	printf("请输入数据规模：\n");
	scanf("%d",&n);
	while(n>0)
	{
		T=createbst(n);//创建BST
		printf("创建好的BST为：\n");
		showbst(T);//显示BST
		printf("\n\n该BST查找成功的平均查找长度=%.2f\n\n",comasl(T));//计算BST查找成功的ASL
		for(i=1;T&&i<=4;i++)
		{
//////////////////////做连续四次的删除，待删除数据随机生成///////////////////////////////////////////////
			x=rand()%23;
			printf(" \n删除数据%d后，BST为：\n",x);	
			T=delnode(T,x);//在BST中做删除
			showbst(T);
			printf("\n\n");	
		}
		T=delbst(T);//销毁BST
		printf("请输入数据规模：\n");
	    scanf("%d",&n);
	}
}


BST *createbst(int n)
{
	int i,x;
	BST *T=NULL;
	srand(time(0));
	for(i=0;i<n;i++)
	{
		x=rand()%23;//随机生成的数据均小于23，方便调试，这个可以自行调整
		T=insnode(T,x);
	}
	return T;
}

BST *delbst(BST *T)//销毁BST
{
	if(!T)
		return NULL;
	else
	{
		T->left=delbst(T->left);
		T->right=delbst(T->right);
		free(T);
		return NULL;
	}
}

BST *insnode(BST *T,int x)//在BST中做插入，并返回根节点指向
{
    if(T == nullptr)
    {
        BST *temp = (BST *)malloc(sizeof(BST));
        temp->data = x;
        temp->left = temp->right = nullptr;
        return temp;
    }
    if(x < T->data)T->left = insnode(T->left , x);
    else if(x > T->data)T->right = insnode(T->right , x);
	return T;
}

BST *Find_min(BST *T)
{
    BST *temp = T;
    while(temp->left != nullptr)temp = temp->left;
    return temp;
}

BST *delnode(BST *T,int x)//在BST中做删除并返回根节点指向。如果x不存在，给出提示信息“该数据不存在”
{
    if(T == nullptr)
    {
        cout << "该数据不存在" << endl;
        return T;
    }
    if(T->data == x && T->left == nullptr && T->right == nullptr)
    {
        free(T);
        T = nullptr;
        return T;
    }
    if(T->data == x)
    {
        BST *temp;
        if(T->left == nullptr)
        {
            temp = T->right;
            free(T);
            T = nullptr;
            return temp;
        }
        else if(T->right == nullptr)
        {
            temp = T->left;
            free(T);
            T = nullptr;
            return temp;
        }
        else
        {
            temp = Find_min(T->right);
            T->data = temp->data;
            delnode(T->right , temp->data);
            return T;
        }
    }
    else if(x < T->data)T->left = delnode(T->left , x);
    else T->right = delnode(T->right , x);
    return T;
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

float comasl(BST *T)//计算BST的平均查找长度
{
    float sum = 0;
    queue<BST *> q;
    BST *end = T;
    float time = 1;
    int count = 0;
    q.push(T);
    while(!q.empty())
    {
        BST *temp = q.front();
        q.pop();
        if(temp == nullptr)continue;
        q.push(temp->left);
        q.push(temp->right);
        sum += float(time);
        count ++;
        while(temp != end)
        {
            temp = q.front();
            q.pop();
            if(temp == nullptr)continue;
            q.push(temp->left);
            q.push(temp->right);
            sum += float(time);
            count ++;
        }
        end = q.back();
        time ++;
    }
    return sum / float(count);
}









