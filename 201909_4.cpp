//
// Created by haoha on 2019/10/22.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Node
{
    int type;
    long long int id;
    int score;
    friend bool operator<(const Node &a , const Node &b){if(a.score == b.score)if(a.type == b.type)return a.id < b.id;else return a.type < b.type;else return a.score > b.score;};
};

int main()
{
    long long int mul = (1e9);
    set<Node> ans;
    unordered_map<long long int , set<Node>::iterator> pos;
    int m , n;
    cin >> m >> n;
    for(int i = 1;i <= n;i ++)
    {
        long long int id;
        int score;
        cin >> id >> score;
        for(int j = 0;j < m;j ++)
        {
            Node t{};
            t.type = j;
            t.id = id * mul + t.type;
            t.score = score;
            pos.insert(make_pair(t.id , ans.insert(t).first));
        }
    }
    int op_num;
    cin >> op_num;
    for(int time = 0;time < op_num;time ++)
    {
        int choice;
        cin >> choice;
        if(choice == 1)
        {
            Node t{};
            cin >> t.type >> t.id >> t.score;
            t.id = t.id * mul + t.type;
            pos.insert(make_pair(t.id , ans.insert(t).first));
        }
        else if(choice == 2)
        {
            int type;
            long long int name;
            cin >> type >> name;
            auto x = pos.find(name * mul + type)->second;
            ans.erase(x);
            pos.erase(name * mul + type);
        }
        else if(choice == 3)
        {
            vector<vector<Node> >out(m);
            int type[50];
            int k;
            cin >> k;
            int sum = 0;
            for(int i = 0;i < m;i ++)cin >> type[i];
            for(const auto &x: ans)
            {
                if(type[x.type] > 0)
                {
                    sum ++;
                    type[x.type] --;
                    out[x.type].push_back(x);
                }
                if(sum == k)break;
            }
            for(auto &x: out)
            {
                if(x.empty())cout << "-1" << endl;
                else
                {
                    sort(x.begin() , x.end());
                    for(auto &y :x)
                    {
                        y.id = (y.id - y.type) / mul;
                        cout << y.id << ' ';
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}