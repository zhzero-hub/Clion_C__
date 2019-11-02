////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：利用孩子-兄弟法表示树，完成下列操作：
//
//          1、以括号的形式显示树；A(B(E,F),C,D(G(H,I,J)))
//          2、利用递归算法输出根节点到所有叶子节点的路径；
//          3、利用非递归算法输出根节点到所有叶子节点的路径；
//          4、计算树的高度；
//          5、统计树中叶子节点的数量；
//          6、层次遍历树，逐行输出各个层次的节点，并计算树的宽度（包含最多节点的层次所实际包含的节点数即树的宽度）
//          7、利用递归算法为每个节点的pa指针赋值，指向该节点的父节点
//          8、复制一个与该树一模一样的树，并返回复制树的根节点指针
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
#define N 30

typedef struct node
{
    char data;
    struct node *fir,*sib;
    struct node *pa;
}TR;


int menu_select();
TR *createtree(char *pre,int *k);//根据树的先序序列（包含空格）创建二叉树，*k表示当前先序序列中的第*k个位置，该位置上
//如果是空格，则返回一个空指针，如果是一个确定的字符，则创建一个节点，该节点数据为
//pre[*k]，然后对(*k)++,递归的创建该节点的孩子分支，然后对(*k)++,再递归的创建它的兄弟分支，
//最后返回该节点指针。（注意在该过程中不要对pa指针赋值。）

void showtree(TR *T);//用括号的形式输出树
void getpath1(TR *T , vector<TR *> &path);//设计递归算法输出根节点到所有叶子节点的路径
void getpath2(TR *T);//设计非递归算法输出根节点到所有叶子节点的路径
int heighttree(TR *T);///计算并返回树的高度
int leaftree(TR *T);//计算并返回树的叶子节点的数量
int layervisit(TR *T);//逐行输出树各个层次的节点,并返回树的宽度
void getpa(TR *T);//为每个节点的pa指针赋值，指向该节点的父节点，根节点的pa指向NULL
void showpa(TR *T);//显示每个节点及其父节点
TR *copytree(TR *T);//复制一个与该树一模一样的树，并返回复制的树的根节点指向
TR *deltree(TR *T);//销毁树




int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.创建孩子-兄弟二叉树\n");
        printf("2.显示树\n");
        printf("3.输出根节点到所有叶子节点的路径\n");
        printf("4.树的高度和叶子节点数量\n");
        printf("5.层次遍历树\n");
        printf("6.获取pa指针\n");
        printf("7.复制树\n");
        printf("0.exit\n");
        printf("Please input index(0-7):");
        i=getchar();
    }while(i<'0' || i>'7');
    return (i-'0');
}



int main()
{
    char pre[]="ABE F  C DGH I J     ";//已知树的先序序列(空格对应空指向)
    TR *T=nullptr,*R=nullptr;
    int k;
    vector<TR *> path;
    for(;;)
    {
        switch(menu_select())
        {
            case 1:
                k=0;
                T=createtree(pre,&k);//创建树
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
                    showtree(T);//显示树
                printf("\n");
                system("pause");
                break;
            case 3:
                printf("\n递归算法得到根节点到所有叶子节点的路径：\n");
                getpath1(T , path);//递归算法找路径
                printf("\n非递归算法得到根节点到所有叶子节点的路径：\n");
                getpath2(T);//非递归算法找路径
                system("pause");
                break;
            case 4:
                printf("\n树的高度=%d ,树中包含 %d 片叶子\n",heighttree(T),leaftree(T));//统计数的高度和叶子节点数量
                system("pause");
                break;
            case 5:
                printf("\n树的层次遍历结果：\n");
                k=layervisit(T);//逐行显示各个层次的节点，并返回树的宽度
                printf("\n树的宽度为：%d\n",k);
                system("pause");
                break;
            case 6:
                getpa(T);//给每个节点的pa指针赋值
                printf("\n树的节点及其对应父节点:\n");
                showpa(T);//显示树的所有节点及其对应父节点
                system("pause");
                break;
            case 7:
                R=copytree(T);//复制一个与根结点为T的树一模一样的树，将复制树的根节点指向返回赋值给R
                T=deltree(T);//销毁原树
                printf("\n复制的树：\n");
                showtree(R);//显示复制的树R
                printf("\n");
                R=deltree(R);//销毁复制的树
                system("pause");
                break;
            case 0:
                printf("GOOD BYE\n");
                system("pause");
                exit(0);
        }
    }
}


TR *createtree(char *pre,int *k)//根据树的先序序列创建二叉树
{
////////////////////////////////////please complete the function///////////////////////////////////////////////////////
    TR *p;
    if(pre[*k]==' ')
    {
        (*k)++;
        return nullptr;
    }
    else
    {
        p=(TR *)malloc(sizeof(TR));
        p->data=pre[*k];
        (*k)++;
        p->fir=createtree(pre,k);
        p->sib=createtree(pre,k);
        return p;
    }
}

void showtree(TR *T)//用括号的形式输出二叉树
{
    if(T == nullptr)return;
    cout << T->data;
    if(T->fir != nullptr)
    {
        cout << "(";
        showtree(T->fir);
        cout << ")";
    }
    if(T->sib != nullptr)
    {
        cout << ",";
        showtree(T->sib);
    }
}


void getpath1(TR *T , vector<TR *> &path)//递归算法输出根节点到所有叶子节点的路径
{
    if(T->fir == nullptr)
    {
        for(const auto &x: path)cout << x->data << "-->";
        cout << T->data << endl;
        if(T->sib != nullptr)getpath1(T->sib , path);
        return;
    }
    path.push_back(T);
    getpath1(T->fir , path);
    path.pop_back();
    if(T->sib != nullptr)getpath1(T->sib , path);
}


void getpath2(TR *T)//非递归算法输出根节点到所有叶子节点的路径
{
    vector<TR *> path;
    unordered_set<TR *> visit;
    path.push_back(T);
    visit.insert(T);
    while(!path.empty())
    {
        TR *p = path.back();
        bool find = false;
        if(p->fir == nullptr)
        {
            for(const auto &x: path)cout << x->data << ' ';
            cout << endl;
        }
        else if(visit.find(p->fir) == visit.end())
        {
            path.push_back(p->fir);
            visit.insert(p->fir);
            continue;
        }
        if(p->sib != nullptr)
        {
            path.pop_back();
            while(p->sib != nullptr)
            {
                if(visit.find(p->sib) == visit.end())
                {
                    path.push_back(p->sib);
                    visit.insert(p->sib);
                    find = true;
                    break;
                }
                p = p->sib;
            }
        }
        if(!find)path.pop_back();
    }
}


int heighttree(TR *T)///计算并返回树的高度
{
    if(T == nullptr)return 0;
    else if(T->fir == nullptr)return 1;
    int height = heighttree(T->fir) + 1;
    TR *p = T;
    while(p->sib != nullptr)
    {
        int temp = heighttree(p->sib);
        p = p->sib;
        if(temp > height)height = temp;
    }
    return height;
}

int leaftree(TR *T)//计算并返回树的叶子节点的数量
{
    int ans = 0;
    if(T->fir == nullptr)
    {
        ans ++;
        if(T->sib != nullptr)ans += leaftree(T->sib);
        return ans;
    }
    ans += leaftree(T->fir);
    if(T->sib != nullptr)ans += leaftree(T->sib);
    return ans;
}


int layervisit(TR *T)//逐行输出树的各个层次，并返回树的宽度
{
    if(T == nullptr)return 0;
    int count = 1;
    queue<TR *>q;
    q.push(T);
    TR *pos = T;
    while(!q.empty())
    {
        int temp = 0;
        TR *p = nullptr;
        while(p != pos)
        {
            p = q.front();
            cout << p->data << ' ';
            TR *t = p->fir;
            while(t != nullptr) {
                q.push(t);
                t = t->sib;
            }
            q.pop();
            temp ++;
        }
        cout << endl;
        pos = q.back();
        if(count < temp)count = temp;
    }
    return count;
}

void getpa(TR *T)//为每个节点的pa指针赋值，指向该节点的父节点，根节点的pa指向NULL
{
    if(T == nullptr)return;
    T->pa = nullptr;
    TR *q = T;
    while(q != nullptr)
    {
        if(q->fir != nullptr)
        {
            getpa(q->fir);
            TR *p = q->fir;
            while(p != nullptr)
            {
                p->pa = q;
                p = p->sib;
            }
        }
        q = q->sib;
    }
}




void showpa(TR *T)//显示每个节点及其父节点
{
    if(T)
    {
        if(T->pa)
            printf("%c---%c\n",T->data,T->pa->data);
        else
            printf("%c---NULL\n",T->data);
        showpa(T->fir);
        showpa(T->sib);
    }
}

TR *copytree(TR *T)//复制树
{
    if(T == nullptr)return nullptr;
    TR *ans = (TR *)malloc(sizeof(TR));
    ans->data = T->data;
    ans->fir = copytree(T->fir);
    TR *p = T;
    TR *q = ans;
    while(p != nullptr)
    {
        q->sib = copytree(p->sib);
        p = p->sib;
        q = q->sib;
    }
    return ans;
}

TR *deltree(TR *T)//销毁树
{
    if(T)
    {
        T->fir=deltree(T->fir);
        T->sib=deltree(T->sib);
        free(T);
        return nullptr;
    }
    else
        return nullptr;
}





