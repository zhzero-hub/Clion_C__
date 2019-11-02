//
// Created by haoha on 2019/10/28.
//

#include <iostream>
#include <string>
using namespace std;

const int mod = 1e9 + 7;

void Ans(int n , const string& num , int& ans)
{
    if(num.size() == n)
    {
        if(num[0] == '0')return;
        int a[4] = {};
        int check_l = 0 , check_r = 0;
        for(auto x: num)
        {
            a[x - '0'] ++;
            if(x == '0' && check_l)return;
            else if(x == '1')check_l = 1;
            else if(x == '2' && check_r)return;
            else if(x == '3')check_r = 1;
        }
        for(auto x: a)if(!x)return;
        ans ++;
        ans = ans % mod;
    }
    else
    {
            Ans(n, num + "0", ans);
            Ans(n, num + "2", ans);
            Ans(n , num + "1" , ans);
            Ans(n , num + "3" , ans);
    }
}

int main()
{
    for(int i = 4;i <= 1000;i ++)
    {
        int ans = 0;
        string num = "2";
        Ans(i , num , ans);
        cout << ans << ',';
    }
}