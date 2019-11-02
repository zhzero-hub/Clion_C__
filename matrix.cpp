///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：用三元组表示稀疏矩阵A与B，设计算法实现两个稀疏矩阵的加法以及快速逆置处理，分析相加以及逆置的时间复杂度
//          矩阵A：0    3    0     0
//                 0   -1    0    12
//                 9    0    0     0
//
//          矩阵B：0    0    0     4
//                 0    1    5     0
//                 2    -6   0     0
//
//
//学号：161820217
//姓名：郑好
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#define N 30
typedef struct mytripple//定义三元组
{
    int i,j,data;
}TR;

typedef struct mymatrix//定义稀疏矩阵的数据结构
{
    TR T[N];//三元组数组
    int mu,nu,tu;//mu表示行数,nu表示列数,tu表示非零元的个数
}MA;

void showmatrix(MA *A);//显示稀疏矩阵
MA reversema(MA *A);//对稀疏矩阵进行快速逆置，并返回逆置结果
void init(MA *A,MA *B);//对稀疏矩阵初始化，赋初始值
MA addition(MA *A,MA *B);//将两个稀疏矩阵相加，并返回结果
int main()
{
    MA A,B;
    init(&A,&B);//对两个稀疏矩阵赋值
    printf("the original matrix A is:\n");
    showmatrix(&A);//显示稀疏矩阵A
    printf("the original matrix B is:\n");
    showmatrix(&B);//显示稀疏矩阵B
    A=addition(&A,&B);//将A与B相加并将结果返回给A
    printf("the result of addition is:\n");
    showmatrix(&A);	//显示相加的结果
    A=reversema(&A);//将矩阵A逆置
    printf("after reverse,the matrix is:\n");
    showmatrix(&A);//显示逆置后的结果
}

void showmatrix(MA *A)
{
    int i,j,k;//i表示行号，j表示列号，k表示三元组中非零元的序号
    for(i=1,k=1;i<=A->mu;i++)
    {
        for(j=1;j<=A->nu;j++)
        {
            if(A->T[k].i==i&&A->T[k].j==j)
            {
                printf("%4d",A->T[k].data);
                k++;
            }
            else
                printf("   0");
        }
        printf("\n");
    }
    printf("\n");
}



MA reversema(MA *A)
{
    MA ans;
    int num[110] = {};//num[i]对应矩阵中第i列一共有多少个非零元
    int pos[110] = {};//pos[i]对应矩阵中第i列的第一个元素应当放在逆置的三元表的位置
    //公式为：pos[i] = pos[i - 1] + num[i - 1]，其中，pos[1] = 1
    for(int i = 1;i <= A->tu;i ++)num[A->T[i].j] ++;//记录每一列非零元的个数
    pos[1] = 1;
    for(int i = 2;i <= A->nu;i ++)pos[i] = pos[i - 1] + num[i - 1];//计算第i列的第一个元素应当放在逆置的三元表的位置
    for(int i = 1;i <= A->tu;i ++)
    {
        int pos_j = A->T[i].j;
        int new_pos = pos[pos_j] ++;//该列每存储过一个元素后，需要对原存储位置+1，防止下一个元素覆盖上一个元素
        TR temp = A->T[i];
        temp.j = temp.i;
        temp.i = pos_j;
        ans.T[new_pos] = temp;
    }
    ans.tu = A->tu;
    ans.mu = A->nu;
    ans.nu = A->mu;
    return ans;
}

MA addition(MA *A,MA *B)
{
    MA ans;
    int pos_a = 1;//对应矩阵A中的指针
    int pos_b = 1;//对应矩阵B中的指针
    int pos = 1;//对应矩阵ans中的指针
    while(pos_a <= A->tu && pos_b <= B->tu)
    {
        if(A->T[pos_a].i == B->T[pos_b].i)
        {
            if(A->T[pos_a].j == B->T[pos_b].j)
            {
                ans.T[pos] = A->T[pos_a];
                ans.T[pos].data += B->T[pos_b].data;
                pos_a ++;
                pos_b ++;
                if(ans.T[pos].data == 0)continue;//相加后元素为0，不存储，所以pos不加
                pos ++;
            }
            else if(A->T[pos_a].j < B->T[pos_b].j)
            {
                ans.T[pos] = A->T[pos_a];
                pos_a ++;
                pos ++;
            }
            else
            {
                ans.T[pos] = B->T[pos_b];
                pos_b ++;
                pos ++;
            }
        }
        else if(A->T[pos_a].i < B->T[pos_b].i)
        {
            ans.T[pos] = A->T[pos_a];
            pos_a ++;
            pos ++;
        }
        else
        {
            ans.T[pos] = B->T[pos_b];
            pos_b ++;
            pos ++;
        }
    }
    while(pos_a <= A->tu)
    {
        ans.T[pos] = A->T[pos_a];
        pos_a ++;
        pos ++;
    }
    while(pos_b <= B->tu)
    {
        ans.T[pos] = B->T[pos_b];
        pos_b ++;
        pos ++;
    }
    ans.tu = -- pos;
    ans.mu = A->mu;
    ans.nu = A->nu;
    return ans;
}

void init(MA *A,MA *B)
{
    A->mu=3;
    A->nu=4;
    A->tu=4;
    A->T[1].data=3;
    A->T[1].i=1;
    A->T[1].j=2;
    A->T[2].data=-1;
    A->T[2].i=2;
    A->T[2].j=2;
    A->T[3].data=12;
    A->T[3].i=2;
    A->T[3].j=4;
    A->T[4].data=9;
    A->T[4].i=3;
    A->T[4].j=1;
///////////////////////////////////////////////////////////////////
    B->mu=3;
    B->nu=4;
    B->tu=5;
    B->T[1].data=4;
    B->T[1].i=1;
    B->T[1].j=4;
    B->T[2].data=1;
    B->T[2].i=2;
    B->T[2].j=2;
    B->T[3].data=5;
    B->T[3].i=2;
    B->T[3].j=3;
    B->T[4].data=2;
    B->T[4].i=3;
    B->T[4].j=1;
    B->T[5].data=-6;
    B->T[5].i=3;
    B->T[5].j=2;

}