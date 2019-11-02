//
// Created by haoha on 2019/10/25.
//

#include <iostream>
using namespace std;

int main()
{
    int drop[1010] = {};
    int num[1010] = {};
    int n;
    cin >> n;
    for(int time= 1;time <= n;time ++)
    {
        int m;
        cin >> m >> num[time];
        for(int i = 1;i < m;i ++)
        {
            int temp;
            cin >> temp;
            if(temp > 0)
            {
                if(num[time] > temp)
                {
                    num[time] = temp;
                    drop[time] ++;
                }
            }
            else
            {
                num[time] += temp;
            }
        }
    }
    int count = 0;
    int sum = 0;
    int ans = 0;
    for(int i = 1;i <= n;i ++)
    {
        sum += num[i];
        if(drop[i])count ++;
    }
    for(int i = 2;i < n;i ++)if(drop[i - 1] && drop[i] && drop[i + 1])ans ++;
    if(drop[n - 1] && drop[n] && drop[1])ans ++;
    if(drop[n] && drop[1] && drop[2])ans ++;
    cout << sum << ' ' << count << ' ' << ans;
}