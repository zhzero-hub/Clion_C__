///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ������Ԫ���ʾϡ�����A��B������㷨ʵ������ϡ�����ļӷ��Լ��������ô�����������Լ����õ�ʱ�临�Ӷ�
//          ����A��0    3    0     0
//                 0   -1    0    12
//                 9    0    0     0
//
//          ����B��0    0    0     4
//                 0    1    5     0
//                 2    -6   0     0
//
//
//ѧ�ţ�161820217
//������֣��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#define N 30
typedef struct mytripple//������Ԫ��
{
    int i,j,data;
}TR;

typedef struct mymatrix//����ϡ���������ݽṹ
{
    TR T[N];//��Ԫ������
    int mu,nu,tu;//mu��ʾ����,nu��ʾ����,tu��ʾ����Ԫ�ĸ���
}MA;

void showmatrix(MA *A);//��ʾϡ�����
MA reversema(MA *A);//��ϡ�������п������ã����������ý��
void init(MA *A,MA *B);//��ϡ������ʼ��������ʼֵ
MA addition(MA *A,MA *B);//������ϡ�������ӣ������ؽ��
int main()
{
    MA A,B;
    init(&A,&B);//������ϡ�����ֵ
    printf("the original matrix A is:\n");
    showmatrix(&A);//��ʾϡ�����A
    printf("the original matrix B is:\n");
    showmatrix(&B);//��ʾϡ�����B
    A=addition(&A,&B);//��A��B��Ӳ���������ظ�A
    printf("the result of addition is:\n");
    showmatrix(&A);	//��ʾ��ӵĽ��
    A=reversema(&A);//������A����
    printf("after reverse,the matrix is:\n");
    showmatrix(&A);//��ʾ���ú�Ľ��
}

void showmatrix(MA *A)
{
    int i,j,k;//i��ʾ�кţ�j��ʾ�кţ�k��ʾ��Ԫ���з���Ԫ�����
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
    int num[110] = {};//num[i]��Ӧ�����е�i��һ���ж��ٸ�����Ԫ
    int pos[110] = {};//pos[i]��Ӧ�����е�i�еĵ�һ��Ԫ��Ӧ���������õ���Ԫ���λ��
    //��ʽΪ��pos[i] = pos[i - 1] + num[i - 1]�����У�pos[1] = 1
    for(int i = 1;i <= A->tu;i ++)num[A->T[i].j] ++;//��¼ÿһ�з���Ԫ�ĸ���
    pos[1] = 1;
    for(int i = 2;i <= A->nu;i ++)pos[i] = pos[i - 1] + num[i - 1];//�����i�еĵ�һ��Ԫ��Ӧ���������õ���Ԫ���λ��
    for(int i = 1;i <= A->tu;i ++)
    {
        int pos_j = A->T[i].j;
        int new_pos = pos[pos_j] ++;//����ÿ�洢��һ��Ԫ�غ���Ҫ��ԭ�洢λ��+1����ֹ��һ��Ԫ�ظ�����һ��Ԫ��
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
    int pos_a = 1;//��Ӧ����A�е�ָ��
    int pos_b = 1;//��Ӧ����B�е�ָ��
    int pos = 1;//��Ӧ����ans�е�ָ��
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
                if(ans.T[pos].data == 0)continue;//��Ӻ�Ԫ��Ϊ0�����洢������pos����
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