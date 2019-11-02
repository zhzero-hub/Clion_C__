//
// Created by haoha on 2019/10/29.
//

#include <iostream>
#include <queue>
#include <string>
#include <stack>
#include <vector>
#include <unordered_set>
using namespace std;

int main()
{
    int m , n;
    cin >> n >> m;
    getchar();
    for(int time = 1;time <= n;time ++)
    {
        int sum = 0;
        vector<pair<queue<int> , int> > vec(m);
        for(int i = 0;i < m;i ++)
        {
            string temp;
            getline(cin , temp);
            int size = temp.size();
            vec[i].second = 0;//0表示可以取出前一个元素
            for(int x = 0;x < size;x ++)
            {
                int t = 100000000;
                int sig = 0;
                if(temp[x] == 'R')sig = 0;
                else sig = 1;
                x ++;
                int u = 0;
                while(temp[x] >= '0' && temp[x] <= '9')
                {
                    u *= 10;
                    u += temp[x] - '0';
                    x ++;
                }
                t += u * 10000 + i;
                if(sig) t = -t;
                vec[i].first.push(t);
                sum ++;
            }
        }
        if(sum % 2)
        {
            cout << '1' << endl;
            continue;
        }
        unordered_set<int> ans;
        int count = 0;
        while(count < sum)
        {
            int num = 0;
            for(auto &x: vec)
            {
                if(!x.second)
                {
                    int t = x.first.front();
                    int u = t;
                    x.first.pop();
                    int p = 0 , q = 0;
                    if(t > 0)
                    {
                        t -= 100000000;
                        q = t / 10000;
                        p = t % 10000;
                        t = -100000000 - p * 10000 - q;
                    } else{
                        t += 100000000;
                        q = t / 10000;
                        p = t % 10000;
                        t = 100000000 - p * 10000 - q;
                    }
                    auto y = ans.find(t);
                    if(y != ans.end())
                    {
                        ans.erase(y);
                        if(q < 0)q = -q;
                        vec[q].second = 0;
                        count += 2;
                    }
                    else
                    {
                        x.second = 1;
                        ans.insert(u);
                    }
                }
                else num ++;
            }
            if(num == m)
            {
                cout << '1' << endl;
                break;
            }
        }
        if(count == sum)cout << '0' << endl;
    }
}