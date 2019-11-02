////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ�����ö�������ʾ��������������в�����
//          1�����ݶ������������������д����������������ظ��ڵ�ָ�룻
//          2�����õݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          3�����÷ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          4�����õݹ��㷨��Ѱ�Ҿ�������ָ���ڵ㣨���಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ�룻
//          5������η�������������Ľڵ����ݣ�ÿ���㵥��һ����ʾ�������жϸö������Ƿ�Ϊ��ȫ������
//          6��������ָ���ڵ�Ϊ���ڵ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
#define N 30

typedef struct node
{
	char data;
	struct node *left,*right = nullptr;
}BT;

int menu_select();

BT *createtree(char *in,char *pre,int k , int l , int r , int &i);//���ݶ�������������������д�����������k��ʾ�ַ���in�ĳ���
void showtree(BT *T);//�����ŵ���ʽ���������
void getpath1(BT *T , vector<char> &ans);//�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
void getpath2(BT *T);//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
BT *delsubtree(BT *T,char s , bool &check);//�ҵ���������Ϊs�Ľڵ㣬��ɾ���Ըýڵ�Ϊ������������󷵻ظ��ڵ㣨��Ϊ���ɾ��Ҳ���ܻ�ɾ����������
int getcomances(BT *T,char s1,char s2 , BT &ans);//Ѱ�Ҿ�������ָ���ڵ�s1��s2�����಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ��
int layervisit(BT *T);//��α�������������������ڵ����ݣ����жϸö������Ƿ�Ϊ��ȫ������������ǣ�����1�����򷵻�0





int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.����������\n");
		printf("2.��ʾ������\n");
		printf("3.������ڵ㵽����Ҷ�ӽڵ��·��\n");
		printf("4.Ѱ�Ҿ��������ڵ�����Ĺ�ͬ����\n");
		printf("5.��α���������\n");	
		printf("6.������ָ���ڵ�Ϊ���ڵ������\n");	
		printf("0.exit\n");
		printf("Please input index(0-6):");
		i=getchar();		
	}while(i<'0' || i>'6');
	return (i-'0');	
}



int main()
{
	BT *T=nullptr;
	BT p;
	char in[]="GBEHDFAC",pre[]="ABGDEHFC";//��֪���������������������
	char s;
	int tree_pos = 0;
	bool check = false;
	vector<char> Path;
	int status = 0;
	int k=strlen(in);//k��ʾ�������г���
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
            T=createtree(in,pre,k , 0 , k - 1 , tree_pos);
			if(T)
				printf("�����ɹ�\n");
			else
				printf("�������ɹ�\n");
			system("pause");
			break;
		case 2:
			if(!T)
				printf("���ǿ���\n");
			else
				showtree(T);
			printf("\n");
			system("pause");				
			break;
		case 3:			    			
			printf("\n�ݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath1(T , Path);
			printf("\n�ǵݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath2(T);
			system("pause");		
			break;
		case 4:			    
			getcomances(T,'H','F' , p);//Ѱ�Ҿ���H��F�ڵ�����Ĺ�ͬ����
	        printf("\n���� H �� F ����Ĺ�ͬ�����ǣ� %c\n",p.data);//����ҵ������Ƚڵ����ݣ�Ӧ����D
	        getcomances(T,'H','G' , p);//Ѱ�Ҿ���H��G�ڵ�����Ĺ�ͬ����
	        printf("\n���� H �� G ����Ĺ�ͬ�����ǣ� %c\n",p.data);//����ҵ������Ƚڵ����ݣ�Ӧ����B
			system("pause");
			break;
		case 5:	
			printf("\n��������α��������\n");
			if(layervisit(T))
				printf("�ö���������ȫ������\n");
			else
				printf("�ö�����������ȫ������\n");
			system("pause");
			break;
		case 6:	
			T=delsubtree(T,'D' , check);//ɾ����D��Ϊ���ڵ������
			printf("\nɾ����DΪ���ڵ������������Ϊ:\n",s);
			if(!T)
				printf("��Ϊ��\n");
			else
	            showtree(T);//��ʾɾ�������
			system("pause");
			break;		
		case 0:
			 printf("GOOD BYE\n");
			 system("pause");
				exit(0);
		}
	}
}

int Find(const char *str , char &x , int n)//���ַ����в����ַ�x��λ�ã��Ҳ�������-1
{
    for(int i = 0;i < n;i ++)if(str[i] == x)return i;
    return -1;
}

BT *createtree(char *in,char *pre,int k , int l , int r , int &i)//���ݶ�������������������д�����������k��ʾ�ַ���in�ĳ���
{
    if(l == r)
    {
        node *p = (node *)malloc(sizeof(node));
        p->data = pre[i];
        p->left = p->right = nullptr;
        i ++;
        return p;
    }
    else if(r - l == 1)
    {
        node *p = (node *)malloc(sizeof(node));
        p->data = pre[i];
        p->left = p->right = nullptr;
        int mid = Find(in , pre[i] , k);
        i ++;
        int temp = Find(in , pre[i] , k);
        node *q = (node *)malloc(sizeof(node));
        q->data = pre[i];
        q->left = q->right = nullptr;
        i ++;
        if(temp < mid)p->left = q;
        else if(temp > mid)p->right = q;
        return p;
    }
    node *p = (node *)malloc(sizeof(node));
    int mid = Find(in , pre[i] , k);
    p->data = pre[i];
    p->left = p->right = nullptr;
    i ++;
    p->left = createtree(in , pre , k , l , mid -  1 , i);
    p->right = createtree(in , pre , k , mid + 1 , r , i);
    return p;
}

void showtree(BT *T)//�����ŵ���ʽ���������
{
	if(T)
	{
		printf("%c",T->data);
		if(T->left||T->right)
		{
			printf("(");
			showtree(T->left);
			printf(",");
			showtree(T->right);
			printf(")");
		}
	}
}

int layervisit(BT *T)//��α�������������������ڵ����ݣ����жϸö������Ƿ�Ϊ��ȫ������������ǣ�����1�����򷵻�0
{
    node *p = T;
    queue<BT *> q;//����������ö��д洢�����ʵĽڵ�
    q.push(p);
    int pos = 1;
    int ans = 0;//ans�����ж��Ƿ�Ϊ��ȫ�����������һ��������ȫ����������ô���ڲ��������ʱ��һ�����ֿ�ָ��Ͳ����ں��������г����µĽڵ�
	while(!q.empty())
    {
	    BT *temp = q.front();
	    q.pop();
	    if(temp != nullptr)
        {
	        if(ans)ans = 2;//ans��Ϊ0�ֳ����µĽڵ㣬˵��������ȫ������
            q.push(temp->left);
            q.push(temp->right);
            cout << "��" << pos << "���ڵ������Ϊ: " << temp->data << endl;
            pos ++;
        }
	    else if(!ans)ans = 1;//��һ�γ��ֿ�ָ�룬ans��Ϊ1
    }
	return ans != 2;
}


void getpath1(BT *T , vector<char> &ans)//�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
    //ans����������¼�ݹ�������߹���·����
    //��Ϊ��Ҫ��������ĸ��ڵ㵽Ҷ�ڵ��·������������¼���ڵݹ�����Ĺ��������������Ҷ�ڵ���һ��·����ͬ����ôֻ����������Ǹ��Ż���������ͬ��·������һ������
    if(T->left == nullptr && T->right == nullptr)//�ҵ�Ҷ�ڵ㣬���
    {
        ans.push_back((T->data));
        for(auto x: ans)cout << x << ' ';
        cout << endl;
        ans.pop_back();
        return;
    }
    if(T->left != nullptr)
    {
        ans.push_back(T->data);
        getpath1(T->left , ans);
        ans.pop_back();
    }
    if(T->right != nullptr)
    {
        ans.push_back(T->data);
        getpath1(T->right , ans);
        ans.pop_back();
    }
}

void getpath2(BT *T)//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
    vector<BT *> ans;//·�����飬��¼�ڵ��Ѿ��߹���·
    int Dir[110] = {};//�������飬���ڼ�¼��Ӧ�Ľڵ��Ƿ񱻷��ʹ�����������������Ϊ1��ʾ���ʹ���������Ϊ2��ʾ���������������������ʹ�
    ans.push_back(T);
    int pos = 0;//pos����ʹ·������ͷ������������ϵ��������ͬһ��pos����¼����Ϣ��Ӧͬһ���ڵ�
    while(pos >= 0)
    {
        BT *p = ans[pos];
        if(p->left == nullptr && p->right == nullptr)
        {
            for(auto x: ans)cout << x->data << ' ';
            cout << endl;
            ans.pop_back();
            pos --;
            continue;
        }
        if(p->left != nullptr && Dir[pos] < 1)//������û�б����ʹ�
        {
            ans.push_back(p->left);
            Dir[pos] = 1;
            pos ++;
        }
        else if(p->right != nullptr && Dir[pos] < 2)//������û�б����ʹ�
        {
            ans.push_back(p->right);
            Dir[pos] = 2;
            pos ++;
        }
        else//���������������ʹ������л���
        {
            ans.pop_back();
            pos --;
        }
    }
}

void Del(BT *T)//�������ɾ���ýڵ�����֮��Ľڵ�
{
    if(T == nullptr)return;
    Del(T->left);
    Del(T->right);
    free(T);
}

BT *delsubtree(BT *T,char s , bool &check)//�ҵ���������Ϊs�Ľڵ㣬��ɾ���Ըýڵ�Ϊ������������󷵻ظ��ڵ㣨��Ϊ���ɾ��Ҳ���ܻ�ɾ����������
{
    //��������ҵ�Ӧɾ���Ľڵ�
    if(T == nullptr)return T;
    if(T->data == s)
    {
        Del(T);
        check = true;//check������¼�Ƿ��Ѿ�ɾ��Ӧ��ɾ���Ľڵ㣬����Ѿ�ɾ������Ϊtrue����ֹ�������û�б�Ҫ�����ĵ�
        return nullptr;
    }
    else
    {
        if(!check)T->left = delsubtree(T->left , s , check);
        if(!check)T->right = delsubtree(T->right , s , check);
    }
    return T;
}

int getcomances(BT *T,char s1,char s2 , BT &ans)//Ѱ�Ҿ�������ָ���ڵ�s1��s2�����಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ��
{
    //0��1��2��ʾѰ��ʱ��״̬�����Ӻ��Һ��ӵ�״̬�ֱ���l��r��¼��
    //�����Ӽ��亢�ӽڵ��������ҪѰ�ҵ�s1��s2����ڵ��lΪ0
    //�����ӻ��亢�ӽڵ㺬��s1��s2�е�һ������ô�ڵ��lΪ1
    //�����ӻ��亢�ӽڵ㺬��s1��s2�У���ô�ڵ��lΪ2
    //�Һ��ӵ�r��lͬ��
    if(T == nullptr)return 0;
    if(T->data == s1 || T->data == s2)
    {
        return 1;
    }
    else
    {
        int l = 0, r = 0;
        l = getcomances(T->left , s1 , s2 , ans);
        if(l == 2)return 2;
        r = getcomances(T->right , s1 , s2 , ans);
        if(l == 1 && r == 1)//������������Ϊ�ݹ����������Ե�һ������l��r��Ϊ1�Ľڵ�һ��������ҪѰ�ҵĽڵ㣬��¼�˽ڵ�����ݺ󷵻�2��ֹ�������ݵĹ�����ans���ı�
        {
            ans = *T;
            return 2;
        }
        else if(l + r == 1)return 1;
        else if(l == 2 || r == 2)return 2;
    }
    return 0;
}







