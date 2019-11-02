//
// Created by haoha on 2019/10/28.
//

#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

struct V
{
    int l = 0;
    int r = 0;
};
struct Node
{
    V v;
    int weight = 0;
    friend bool operator<(const Node &a , const Node &b){return a.weight > b.weight;};
};
int main()
{
    set<Node> path;
    int m , n , k;
    cin >> n >> m >> k;
    int c[10010];
    for(int i = 0;i < m;i ++)cin >> c[i];
    for(int i = 1;i < n;i ++)
    {
        Node temp;
        cin >> temp.v.l >> temp.v.r >> temp.weight;
        path.insert(temp);
    }
}