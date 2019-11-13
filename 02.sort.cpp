///////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ���������n�����������ܻ����ظ�Ԫ�أ���������BST��Ƹ�Ч�㷨�������������
//          ˳��������д��ڵ���k������
//          1���������BST�����ݽṹ�����������Ҫ������Ĺ��ܺ�������Ҫ�޸�main����
//          2�����ݹ�ģn�Լ�k���Ӽ�������
//          3��������ɵ����ݣ���ֵ��Ҫ����100��������Ժ͹۲�������Ҫ�Դ�Ϊ��������㷨        
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

Node *Insert(Node *T,int x)//��BST�������룬�����ظ��ڵ�ָ��
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

void output(int n,int k);//��n��������У�����BST�������������˳��������д��ڵ���k������


int main()
{
	int n,k;
	printf("���������ݹ�ģn�Լ���Ҫ���ҵ��������е���Сֵk:\n");
	scanf("%d%d",&n,&k);
	while(n>0&&k>0)
	{
		printf("���д��ڵ���%d��������:\n",k);
		output(n,k);		
		printf("���������ݹ�ģn�Լ���Ҫ���ҵ��������е����ֵk:\n");
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
