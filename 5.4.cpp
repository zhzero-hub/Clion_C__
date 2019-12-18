//思路是，建立两个一模一样的棋盘a,b，a输入棋子，b不输入（输入都为-1）。当知道a中那些棋子要删去后 
//把b中相同位置的改为0.最后把b中-1的位置输入a中的值，最后输出棋盘b 
#include<iostream>
using namespace std;
int n=0,m=0;
void Change_H(int (*a)[100],int i,int j,int num){
	cout<<i<<j<<num<<endl;
	int x=i;
	for(;x<i+j;x++){
	a[num][x]=0;
	cout<<a[num][x]<<endl;
	}
}
void seek_H(int (*a)[100],int (*b)[100],int i){
	int j=0,sum=0,FI=-1;
	for(;j<n-1;j++){
		if(a[i][j]==a[i][j+1]){
			if(sum==0)FI=j;
			sum++;
		}
		else{
			if(sum>=3)Change_H(b,FI,sum,i);
			FI=-1;
			sum=0;
		}
	}
	if(sum>=3)
	Change_H(b,FI,sum,i);
}
void Change_L(int (*a)[100],int i,int j,int num){
	cout<<i<<j<<num<<endl;
	int x=i;
	for(;x<i+j;x++)
	a[x][num]=0;
}
void seek_L(int (*a)[100],int (*b)[100],int i){
	int j=0,sum=0,FI=-1;
	for(;j<m-1;j++){
		if(a[j][i]==a[j+1][i]){
			if(sum==0)
			FI=j;
			sum++;
		}
		else{
			if(sum>=3)
			Change_L(b,FI,sum,i);
			FI=-1;
			sum=0;
		}
	}
	if(sum>=3)
	Change_L(b,FI,sum,i);
}
int main(){
	int i=0,j=0;
	cout<<"请输入行数和列数："<<endl;
	cin>>n>>m;
	int a[100][100],b[100][100];
	cout<<"请输入棋盘中的棋子，颜色用1到9来表现："<<endl;
	for(;i<n;i++){
		for(j=0;j<m;j++){ 
		cin>>a[i][j];
		b[i][j]=-1;}
	}
	for(i=0;i<m;i++)
	seek_H(a,b,i);
	for(i=0;i<n;i++)
	seek_L(a,b,i);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
		cout<<b[i][j]<<' ';
		cout<<endl;
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(b[i][j]!=0)
			cout<<a[i][j]<<' ';
			else
			cout<<b[i][j]<<' ';
		}
		cout<<endl;
	}
} 
