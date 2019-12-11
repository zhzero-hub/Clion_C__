/////////////////////////////////////////////////////////////////////////////////////////
//
//              ������֣��
//              
//              ѧ�ţ�161820217
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <iostream>
#include <cmath>
using namespace std;


void getdata(int *a,int n);//��ȡn������������������a��
void finddata(int *a,int n);//��n���������Ѱ���Ƿ����ĳ�������ȸ�����ĸ������ڱȸ���С�ĸ�����������з��ϸ���������



int main()
{
	int *a,n;
	printf("\n���������ݹ�ģ\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc(n*sizeof(int));
		getdata(a,n);
		finddata(a,n);
		free(a);
		printf("\n���������ݹ�ģ\n");
	    scanf("%d",&n);
	}
}




void getdata(int *a,int n)//��ȡn������������������a��
{
	int i;
	//srand(time(0));
	for(i=0;i<n;i++)
		a[i]=n-i;
}




////////////////////////////////////////////////////////////////////////////////////////
//     ����ɸú�������n���������Ѱ���Ƿ����ĳ�������ȸ�����ĸ������ڱȸ���С�ĸ�����
//
//     ������з�������������ͬʱ�������С�ͱ���������ĸ�����
//
//     �������������������Ҳ�������ʾ��Ϣ����ʾ��������������
//     
//
/////////////////////////////////////////////////////////////////////////////////////

void qsort(int a[] , int p , int q)
{
	int l = p , r = q;
	int mid = a[(l + r) / 2];
	while(l <= r)
	{
		while(a[l] < mid)l ++;
		while(a[r] > mid)r --;
		if(l <= r)
		{
			int t = a[l];
			a[l] = a[r];
			a[r] = t;
			l ++;
			r --;
		}
	}
	if(l < q)qsort(a , l , q);
	if(r > p)qsort(a , p , r);
}

void finddata(int *a,int n)
{
	qsort(a , 0 , n - 1);
	if(a[0] == a[n - 1])
	{
		cout << "�������־���ͬ" << endl;
		return;
	}
	int pos = n / 2;
	int l = pos - 1;
	int r = pos + 1;
	if(n % 2 == 0)
	{
		if(a[pos] != a[pos - 1])
		{
			cout << "��������������" << endl;
			return;
		}
		else
		{
			l --;
		}
	}
	while(a[l] == a[pos])
	{
		if(a[r] != a[l])
		{
			cout << "��������������" << endl;
			return;
		}
		l --;
		r ++;
	}
	cout << "��Ŀ������Ϊ: " << a[pos] << endl;
	cout << "����Ϊ: " << l + 1 << endl;
}
