//
// Created by haoha on 2019/10/12.
//

#include<iostream>
#include<stack>
#include<vector>
using namespace std;

struct Node
{
    int x;
    int y;
};

bool Check(int *a[] , int x , int y , int n)
{
    int sum = 0;
    for(int i = 1;i <= n;i ++)sum += a[x][i];
    for(int i = 1;i <= n;i ++)sum += a[i][y];
    for(int i = 1;i <= n;i ++)
    {
        if(x - i >= 1 && y - i >= 1)sum += a[x - i][y - i];
        if(x - i >= 1 && y + i <= n)sum += a[x - i][y + i];
        if(x + i <= n && y + i <= n)sum += a[x + i][y + i];
        if(x + i <= n && y - i >= 1)sum += a[x + i][y - i];
    }
    return sum == 0;
}

void Walk(int *a[] , int n)
{
    stack<Node> ans;
    for(int i = 1;i <= n;i ++)
    {
        int count = 0;
        int j , k;
        for(j = 1;j <= n;j ++)
        {
            for(k = 1;k <= n;k ++)
            {
                if(Check(a , j , k , n))
                {
                    count ++;
                    a[j][k] = 1;
                    Node temp{};
                    temp.x = j;
                    temp.y = k;
                    ans.push(temp);
                }
            }

        }
        if(count == n)
        {
            for(int i = 1;i <= n;i ++)
            {
                for(int j = 1;j <= n;j ++)
                {
                    if(a[i][j])
                    {
                        cout << "(" << i << "," << j << ") ";
                        a[i][j] = 0;
                    }
                }
            }
            cout << endl;
        }
    }
}

int main()
{
    int n = 4;
    int a[10][10] = {};
    Walk(a , n);
    system("pause");
}