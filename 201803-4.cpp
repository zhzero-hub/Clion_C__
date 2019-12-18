//
// Created by Z_HAO on 2019/12/12.
//

#include <iostream>
using namespace std;

int a[5][5] = {};

void dfs(const int &person , int i , int j , int flag , int time , bool &ans)
{
    if(time == 3)
    {
        ans = true;
        return;
    }
    if(a[i][j + 1] == person && flag == 1 && !ans)dfs(person , i , j + 1 , flag , time + 1 , ans);
    if(a[i + 1][j] == person && flag == 2 && !ans)dfs(person , i + 1 , j , flag , time + 1 , ans);
    if(a[i + 1][j + 1] == person && flag == 3 && !ans)dfs(person , i + 1 , j + 1 , flag , time + 1 , ans);
    if(a[i - 1][j - 1] == person && flag == 4 && !ans)dfs(person , i - 1 , j - 1 , flag , time + 1 , ans);
}

void place(int *blank , const int &pos , int num , int p)
{
    if(num + 1 > pos)return;

    for(int i = 1;i <= 3;i ++)
    {
        for(int j = 1;j <= 4;j ++)dfs(a[1][i] , 1 , i , j , 1 , ans);
        if(ans)
        {
            if(pos < out)out = pos;
            break;
        }
    }
}

int main()
{
    int blank[10] = {};
    int pos = 0;//pos个空
    int p = 1;
    for(int i = 1;i <= 3;i ++)
        for(int j = 1;j <= 3;j ++)
            cin >> a[i][j];
    for(int i = 1;i <= 3;i ++)
        for(int j = 1;j <= 3;j ++)
            if(!a[i][j])blank[pos ++] = i * 4 + j;
    bool ans = false;
    int out = 10000;

}

















