/////////////////////////////////////////////////////////////////////////////////////////
//
//              姓名：郑好
//              
//              学号：161820217
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <iostream>
#include <cmath>
using namespace std;


void getdata(int *a,int n);//获取n个随机数，存放在数组a中
void finddata(int *a,int n);//在n个随机数中寻找是否存在某个数，比该数大的个数等于比该数小的个数，输出所有符合该条件的数



int main()
{
	int *a,n;
	printf("\n请输入数据规模\n");
	scanf("%d",&n);
	while(n>0)
	{
		a=(int *)malloc(n*sizeof(int));
		getdata(a,n);
		finddata(a,n);
		free(a);
		printf("\n请输入数据规模\n");
	    scanf("%d",&n);
	}
}




void getdata(int *a,int n)//获取n个随机数，存放在数组a中
{
	int i;
	//srand(time(0));
	for(i=0;i<n;i++)
		a[i]=n-i;
}




////////////////////////////////////////////////////////////////////////////////////////
//     请完成该函数。在n个随机数中寻找是否存在某个数，比该数大的个数等于比该数小的个数，
//
//     输出所有符合条件的数，同时输出比它小和比它大的数的个数；
//
//     如果不存在这样的数，也请输出提示信息，表示不存在这样的数
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
		cout << "所有数字均相同" << endl;
		return;
	}
	int pos = n / 2;
	int l = pos - 1;
	int r = pos + 1;
	if(n % 2 == 0)
	{
		if(a[pos] != a[pos - 1])
		{
			cout << "这样的数不存在" << endl;
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
			cout << "这样的数不存在" << endl;
			return;
		}
		l --;
		r ++;
	}
	cout << "题目所求数为: " << a[pos] << endl;
	cout << "个数为: " << l + 1 << endl;
}
