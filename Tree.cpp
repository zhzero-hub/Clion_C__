////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ�����ú���-�ֵܷ���ʾ����������в�����
//
//          1�������ŵ���ʽ��ʾ����A(B(E,F),C,D(G(H,I,J)))
//          2�����õݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          3�����÷ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          4���������ĸ߶ȣ�
//          5��ͳ������Ҷ�ӽڵ��������
//          6����α��������������������εĽڵ㣬���������Ŀ�ȣ��������ڵ�Ĳ����ʵ�ʰ����Ľڵ��������Ŀ�ȣ�
//          7�����õݹ��㷨Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ�
//          8������һ�������һģһ�������������ظ������ĸ��ڵ�ָ��
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
TR *createtree(char *pre,int *k);//���������������У������ո񣩴�����������*k��ʾ��ǰ���������еĵ�*k��λ�ã���λ����
//����ǿո��򷵻�һ����ָ�룬�����һ��ȷ�����ַ����򴴽�һ���ڵ㣬�ýڵ�����Ϊ
//pre[*k]��Ȼ���(*k)++,�ݹ�Ĵ����ýڵ�ĺ��ӷ�֧��Ȼ���(*k)++,�ٵݹ�Ĵ��������ֵܷ�֧��
//��󷵻ظýڵ�ָ�롣��ע���ڸù����в�Ҫ��paָ�븳ֵ����

void showtree(TR *T);//�����ŵ���ʽ�����
void getpath1(TR *T , vector<TR *> &path);//��Ƶݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
void getpath2(TR *T);//��Ʒǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
int heighttree(TR *T);///���㲢�������ĸ߶�
int leaftree(TR *T);//���㲢��������Ҷ�ӽڵ������
int layervisit(TR *T);//���������������εĽڵ�,���������Ŀ��
void getpa(TR *T);//Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ㣬���ڵ��paָ��NULL
void showpa(TR *T);//��ʾÿ���ڵ㼰�丸�ڵ�
TR *copytree(TR *T);//����һ�������һģһ�������������ظ��Ƶ����ĸ��ڵ�ָ��
TR *deltree(TR *T);//������




int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.��������-�ֵܶ�����\n");
        printf("2.��ʾ��\n");
        printf("3.������ڵ㵽����Ҷ�ӽڵ��·��\n");
        printf("4.���ĸ߶Ⱥ�Ҷ�ӽڵ�����\n");
        printf("5.��α�����\n");
        printf("6.��ȡpaָ��\n");
        printf("7.������\n");
        printf("0.exit\n");
        printf("Please input index(0-7):");
        i=getchar();
    }while(i<'0' || i>'7');
    return (i-'0');
}



int main()
{
    char pre[]="ABE F  C DGH I J     ";//��֪������������(�ո��Ӧ��ָ��)
    TR *T=nullptr,*R=nullptr;
    int k;
    vector<TR *> path;
    for(;;)
    {
        switch(menu_select())
        {
            case 1:
                k=0;
                T=createtree(pre,&k);//������
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
                    showtree(T);//��ʾ��
                printf("\n");
                system("pause");
                break;
            case 3:
                printf("\n�ݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
                getpath1(T , path);//�ݹ��㷨��·��
                printf("\n�ǵݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
                getpath2(T);//�ǵݹ��㷨��·��
                system("pause");
                break;
            case 4:
                printf("\n���ĸ߶�=%d ,���а��� %d ƬҶ��\n",heighttree(T),leaftree(T));//ͳ�����ĸ߶Ⱥ�Ҷ�ӽڵ�����
                system("pause");
                break;
            case 5:
                printf("\n���Ĳ�α��������\n");
                k=layervisit(T);//������ʾ������εĽڵ㣬���������Ŀ��
                printf("\n���Ŀ��Ϊ��%d\n",k);
                system("pause");
                break;
            case 6:
                getpa(T);//��ÿ���ڵ��paָ�븳ֵ
                printf("\n���Ľڵ㼰���Ӧ���ڵ�:\n");
                showpa(T);//��ʾ�������нڵ㼰���Ӧ���ڵ�
                system("pause");
                break;
            case 7:
                R=copytree(T);//����һ��������ΪT����һģһ�����������������ĸ��ڵ�ָ�򷵻ظ�ֵ��R
                T=deltree(T);//����ԭ��
                printf("\n���Ƶ�����\n");
                showtree(R);//��ʾ���Ƶ���R
                printf("\n");
                R=deltree(R);//���ٸ��Ƶ���
                system("pause");
                break;
            case 0:
                printf("GOOD BYE\n");
                system("pause");
                exit(0);
        }
    }
}


TR *createtree(char *pre,int *k)//���������������д���������
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

void showtree(TR *T)//�����ŵ���ʽ���������
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


void getpath1(TR *T , vector<TR *> &path)//�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
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


void getpath2(TR *T)//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
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


int heighttree(TR *T)///���㲢�������ĸ߶�
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

int leaftree(TR *T)//���㲢��������Ҷ�ӽڵ������
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


int layervisit(TR *T)//����������ĸ�����Σ����������Ŀ��
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

void getpa(TR *T)//Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ㣬���ڵ��paָ��NULL
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




void showpa(TR *T)//��ʾÿ���ڵ㼰�丸�ڵ�
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

TR *copytree(TR *T)//������
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

TR *deltree(TR *T)//������
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





