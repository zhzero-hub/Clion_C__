//
// Created by haoha on 2019/11/27.
//

#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int data = 0;
    Node *next = nullptr;
};

void dfs(vector<pair<int , Node *>> &vec , Node *x , int *visit , int &ans)
{
    Node *p = vec[x->data].second->next;
    while(p != nullptr && !visit[p->data])
    {
        visit[p->data] = 1;
        ans ++;
        dfs(vec , p , visit , ans);
        visit[p->data] = 0;
        ans --;
    }
}

int main()
{
    int m , n;
    cin >> n >> m;
    vector<pair<int , Node *>> vec(m);
    for(int i = 0;i < m;i ++)
    {
        int num;
        cin >> num;
        vec[i].second = (Node *)malloc(sizeof(Node));
        vec[i].first = i;
        for(int j = 0;j < num;j ++)
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            cin >> temp->data;
            temp->next = nullptr;
            temp->next = vec[i].second->next->next;
            vec[i].second->next = temp;
        }
    }
}