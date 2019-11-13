///////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ����BST��������
//          1������ϵͳ������ɵ����ݴ���BST��
//          2�������BST��ƽ�����ҳ���ASL���ȸ��ʣ����ҳɹ��ģ���
//          3����BST����ɾ��
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

BST *createbst(int n);//����BST
BST *insnode(BST *T,int x);//��BST�в������ݵ�x,�����ظ��ڵ�ָ��
BST *delnode(BST *T,int x);//��BST��ɾ������x�Ľڵ㣬�����ظ��ڵ�ָ��
void showbst(BST *T);//��ʾBST
float comasl(BST *T);//���㲢���صȸ��ʲ����£���BST��ƽ�����ҳ���
BST *delbst(BST *T);//����BST

int main()
{
	int i,n,x;
	BST *T=NULL;
	printf("���������ݹ�ģ��\n");
	scanf("%d",&n);
	while(n>0)
	{
		T=createbst(n);//����BST
		printf("�����õ�BSTΪ��\n");
		showbst(T);//��ʾBST
		printf("\n\n��BST���ҳɹ���ƽ�����ҳ���=%.2f\n\n",comasl(T));//����BST���ҳɹ���ASL
		for(i=1;T&&i<=4;i++)
		{
//////////////////////�������Ĵε�ɾ������ɾ�������������///////////////////////////////////////////////
			x=rand()%23;
			printf(" \nɾ������%d��BSTΪ��\n",x);	
			T=delnode(T,x);//��BST����ɾ��
			showbst(T);
			printf("\n\n");	
		}
		T=delbst(T);//����BST
		printf("���������ݹ�ģ��\n");
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
		x=rand()%23;//������ɵ����ݾ�С��23��������ԣ�����������е���
		T=insnode(T,x);
	}
	return T;
}

BST *delbst(BST *T)//����BST
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

BST *insnode(BST *T,int x)//��BST�������룬�����ظ��ڵ�ָ��
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

BST *delnode(BST *T,int x)//��BST����ɾ�������ظ��ڵ�ָ�����x�����ڣ�������ʾ��Ϣ�������ݲ����ڡ�
{
    if(T == nullptr)
    {
        cout << "�����ݲ�����" << endl;
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

float comasl(BST *T)//����BST��ƽ�����ҳ���
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









