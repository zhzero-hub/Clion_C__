//
// Created by haoha on 2019/10/14.
//

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[10010];
    for(int i = 0;i < n;i ++)cin >> a[i];
    int ans = 0;
    for(int i = 1;i < n;i ++)
    {
        if(a[i] > a[i - 1])
        {
            if(a[i] < a[i + 1])
            {
                ans ++;
                continue;
            }
        }
        else if(a[i] < a[i + 1])
        {
            if(a[i] > a[i + 1])
            {
                ans ++;
                continue;
            }
        }
    }
    cout << ans << endl;
}