//
// Created by Z_HAO on 2019/11/27.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int m , n;
    int ret = 30001;
    cin >> n >> m;
    vector<int> ans(n);
    for(int i = 1;i <= n;i ++)ans[i] = -1;
    for(int i = 1;i <= m;i ++)
    {
        int num , min = 30001;
        cin >> num;
        vector<int> vec;
        for(int j = 1;j <= num;j ++)
        {
            int data;
            cin >> data;
            if(min > data)min = data;
            vec.push_back(data);
        }
        for(int x = 0;x < vec.size();x ++)
        {
            if(vec[x] == min)continue;
            if(ans[vec[x]] == -1)
            {
                ans[vec[x]] = min;
                ans[min] --;
            }
            else if(ans[vec[x]] >= 0)
            {
                int t = ans[vec[x]];
                if(t < min)
                {
                    for(auto &y: ans)if(y == min)y = t;
                    ans[t] -= ans[min];
                    ans[min] = t;
                }
                else {
                    for(auto &y: ans)if(y == t)y = min;
                    ans[min] -= ans[t];
                    ans[t] = min;
                }
            }
            else
            {
                ans[min] -= vec[x];
                for(auto &y: ans)if(y == x)y = min;
            }
        }
    }
    for(const auto &x: ans)if(ret > x)ret = x;
    cout << -ret << endl;
}