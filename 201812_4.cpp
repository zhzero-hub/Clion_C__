//
// Created by haoha on 2019/10/30.
//

#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Node
{
    int l = 0;
    int r = 0;
    int weight = 0;
    friend bool operator<(const Node &a , const Node &b){return a.weight < b.weight;};
};


int main()
{
    set<Node> pos;
    int m , n , base;
    cin >> n >> m >> base;
    for(int i = 1;i <= m;i ++)
    {
        Node temp;
        cin >> temp.l >> temp.r >> temp.weight;
        pos.insert(temp);
    }
    int a[50000] = {};
    int count = 1;
    Node ans;
    for(auto &x: pos)
    {
        if(a[x.l] == 0 || a[x.r] == 0)
        {
            if(x.weight > ans.weight)ans.weight = x.weight;
            count ++;
            a[x.l] ++;
            a[x.r] ++;
        }
    }
    cout << ans.weight;
}