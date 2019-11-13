///////////////////////////////////////////////////////////////////////////////////////////
//题目要求：随机生成n个整数（可能会有重复元素），请利用BST设计高效算法，按降序有序的
//          顺序输出所有大于等于k的数据
//          1、自行设计BST的数据结构，自行设计需要的其余的功能函数，不要修改main函数
//          2、数据规模n以及k均从键盘输入
//          3、随机生成的数据，数值不要超过100，方便调试和观察结果，不要以此为条件设计算法        
//          
////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
const int N = 100;
using namespace std;

struct Node
{
    int data = 0;
    Node *l = nullptr;
    Node *r = nullptr;
};

Node *Insert(Node *T,int x)//在BST中做插入，并返回根节点指向
{
    if(T == nullptr)
    {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = x;
        temp->l = temp->r = nullptr;
        return temp;
    }
    if(x < T->data)T->l = Insert(T->l , x);
    else if(x > T->data)T->r = Insert(T->r , x);
    return T;
}

void output(int n,int k);//在n个随机数中，利用BST，按降序有序的顺序输出所有大于等于k的数据


int main()
{
	int n,k;
	printf("请输入数据规模n以及需要查找的有序序列的最小值k:\n");
	scanf("%d%d",&n,&k);
	while(n>0&&k>0)
	{
		printf("所有大于等于%d的数据有:\n",k);
		output(n,k);		
		printf("请输入数据规模n以及需要查找的有序序列的最大值k:\n");
	    scanf("%d%d",&n,&k);
	}
}

void in_order(Node *node , int k)
{
    if(node != nullptr)
    {
        if(node->data < k)return;
        in_order(node->l , k);
        cout << node->data << ' ';
        in_order(node->r , k);
    }
}

void output(int n,int k)
{
    Node *base = nullptr;
    for(int i = 0;i < n;i ++)
    {
        int t = rand() % N;
        base = Insert(base , t);
    }
    in_order(base , k);
    cout << endl;
}
