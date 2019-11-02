////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：利用二叉链表示二叉树，完成下列操作：
//          1、根据二叉树的中序、先序序列创建二叉树，并返回根节点指针；
//          2、利用递归算法输出根节点到所有叶子节点的路径；
//          3、利用非递归算法输出根节点到所有叶子节点的路径；
//          4、利用递归算法，寻找距离两个指定节点（互相不为对方的祖先）最近的共同祖先，返回该祖先指针；
//          5、按层次分行输出二叉树的节点数据（每层结点单独一行显示），并判断该二叉树是否为完全二叉树
//          6、销毁以指定节点为根节点的子树；
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

BT *createtree(char *in,char *pre,int k , int l , int r , int &i);//根据二叉树的中序和先序序列创建二叉树，k表示字符串in的长度
void showtree(BT *T);//用括号的形式输出二叉树
void getpath1(BT *T , vector<char> &ans);//递归算法输出根节点到所有叶子节点的路径
void getpath2(BT *T);//非递归算法输出根节点到所有叶子节点的路径
BT *delsubtree(BT *T,char s , bool &check);//找到包含数据为s的节点，并删除以该节点为根的子树，最后返回根节点（因为这个删除也可能会删除整个树）
int getcomances(BT *T,char s1,char s2 , BT &ans);//寻找距离两个指定节点s1和s2（互相不为对方的祖先）最近的共同祖先，返回该祖先指针
int layervisit(BT *T);//层次遍历二叉树，逐行输出节点数据，并判断该二叉树是否为完全二叉树，如果是，返回1，否则返回0





int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.创建二叉树\n");
		printf("2.显示二叉树\n");
		printf("3.输出根节点到所有叶子节点的路径\n");
		printf("4.寻找距离两个节点最近的共同祖先\n");
		printf("5.层次遍历二叉树\n");	
		printf("6.销毁以指定节点为根节点的子树\n");	
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
	char in[]="GBEHDFAC",pre[]="ABGDEHFC";//已知二叉树的中序和先序序列
	char s;
	int tree_pos = 0;
	bool check = false;
	vector<char> Path;
	int status = 0;
	int k=strlen(in);//k表示中序序列长度
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
            T=createtree(in,pre,k , 0 , k - 1 , tree_pos);
			if(T)
				printf("创建成功\n");
			else
				printf("创建不成功\n");
			system("pause");
			break;
		case 2:
			if(!T)
				printf("树是空树\n");
			else
				showtree(T);
			printf("\n");
			system("pause");				
			break;
		case 3:			    			
			printf("\n递归算法得到根节点到所有叶子节点的路径：\n");
			getpath1(T , Path);
			printf("\n非递归算法得到根节点到所有叶子节点的路径：\n");
			getpath2(T);
			system("pause");		
			break;
		case 4:			    
			getcomances(T,'H','F' , p);//寻找距离H和F节点最近的共同祖先
	        printf("\n距离 H 和 F 最近的共同祖先是： %c\n",p.data);//输出找到的祖先节点数据，应该是D
	        getcomances(T,'H','G' , p);//寻找距离H和G节点最近的共同祖先
	        printf("\n距离 H 和 G 最近的共同祖先是： %c\n",p.data);//输出找到的祖先节点数据，应该是B
			system("pause");
			break;
		case 5:	
			printf("\n二叉树层次遍历结果：\n");
			if(layervisit(T))
				printf("该二叉树是完全二叉树\n");
			else
				printf("该二叉树不是完全二叉树\n");
			system("pause");
			break;
		case 6:	
			T=delsubtree(T,'D' , check);//删除以D作为根节点的子树
			printf("\n删除以D为根节点的子树后，树变为:\n",s);
			if(!T)
				printf("树为空\n");
			else
	            showtree(T);//显示删除后的树
			system("pause");
			break;		
		case 0:
			 printf("GOOD BYE\n");
			 system("pause");
				exit(0);
		}
	}
}

int Find(const char *str , char &x , int n)//在字符串中查找字符x的位置，找不到返回-1
{
    for(int i = 0;i < n;i ++)if(str[i] == x)return i;
    return -1;
}

BT *createtree(char *in,char *pre,int k , int l , int r , int &i)//根据二叉树的中序和先序序列创建二叉树，k表示字符串in的长度
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

void showtree(BT *T)//用括号的形式输出二叉树
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

int layervisit(BT *T)//层次遍历二叉树，逐行输出节点数据，并判断该二叉树是否为完全二叉树，如果是，返回1，否则返回0
{
    node *p = T;
    queue<BT *> q;//层序遍历，用队列存储待访问的节点
    q.push(p);
    int pos = 1;
    int ans = 0;//ans用来判断是否为完全二叉树。如果一棵树是完全二叉树，那么它在层序遍历的时候一旦出现空指针就不能在后续遍历中出现新的节点
	while(!q.empty())
    {
	    BT *temp = q.front();
	    q.pop();
	    if(temp != nullptr)
        {
	        if(ans)ans = 2;//ans不为0又出现新的节点，说明不是完全二叉树
            q.push(temp->left);
            q.push(temp->right);
            cout << "第" << pos << "个节点的数据为: " << temp->data << endl;
            pos ++;
        }
	    else if(!ans)ans = 1;//第一次出现空指针，ans置为1
    }
	return ans != 2;
}


void getpath1(BT *T , vector<char> &ans)//递归算法输出根节点到所有叶子节点的路径
{
    //ans数组用来记录递归过程中走过的路径。
    //因为需要输出完整的根节点到叶节点的路径，若不做记录，在递归输出的过程中如果右两个叶节点有一段路径相同，那么只有先输出的那个才会输出这段相同的路径，后一个不会
    if(T->left == nullptr && T->right == nullptr)//找到叶节点，输出
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

void getpath2(BT *T)//非递归算法输出根节点到所有叶子节点的路径
{
    vector<BT *> ans;//路径数组，记录节点已经走过的路
    int Dir[110] = {};//方向数组，用于记录对应的节点是否被访问过左子树或右子树，为1表示访问过左子树，为2表示左子树和右子树都被访问过
    ans.push_back(T);
    int pos = 0;//pos用来使路径数组和方向数组产生联系，数组内同一个pos处记录的信息对应同一个节点
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
        if(p->left != nullptr && Dir[pos] < 1)//左子树没有被访问过
        {
            ans.push_back(p->left);
            Dir[pos] = 1;
            pos ++;
        }
        else if(p->right != nullptr && Dir[pos] < 2)//右子树没有被访问过
        {
            ans.push_back(p->right);
            Dir[pos] = 2;
            pos ++;
        }
        else//左右子树都被访问过，进行回溯
        {
            ans.pop_back();
            pos --;
        }
    }
}

void Del(BT *T)//后序遍历删除该节点与其之后的节点
{
    if(T == nullptr)return;
    Del(T->left);
    Del(T->right);
    free(T);
}

BT *delsubtree(BT *T,char s , bool &check)//找到包含数据为s的节点，并删除以该节点为根的子树，最后返回根节点（因为这个删除也可能会删除整个树）
{
    //先序遍历找到应删除的节点
    if(T == nullptr)return T;
    if(T->data == s)
    {
        Del(T);
        check = true;//check用来记录是否已经删除应当删除的节点，如果已经删除过置为true，防止后面遍历没有必要遍历的点
        return nullptr;
    }
    else
    {
        if(!check)T->left = delsubtree(T->left , s , check);
        if(!check)T->right = delsubtree(T->right , s , check);
    }
    return T;
}

int getcomances(BT *T,char s1,char s2 , BT &ans)//寻找距离两个指定节点s1和s2（互相不为对方的祖先）最近的共同祖先，返回该祖先指针
{
    //0、1、2表示寻找时的状态。左孩子和右孩子的状态分别用l和r记录。
    //若左孩子及其孩子节点均不含需要寻找的s1和s2，则节点的l为0
    //若左孩子或其孩子节点含有s1或s2中的一个，那么节点的l为1
    //若左孩子或其孩子节点含有s1和s2中，那么节点的l为2
    //右孩子的r与l同理
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
        if(l == 1 && r == 1)//由于搜索过程为递归搜索，所以第一个出现l与r均为1的节点一定就是需要寻找的节点，记录此节点的数据后返回2防止继续回溯的过程中ans被改变
        {
            ans = *T;
            return 2;
        }
        else if(l + r == 1)return 1;
        else if(l == 2 || r == 2)return 2;
    }
    return 0;
}







