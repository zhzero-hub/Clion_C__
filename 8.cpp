//
// Created by haoha on 2019/11/12.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <cstring>
#include <unordered_map>
using namespace std;
const float maxx = 100000;

struct Node//邻接表节点
{
    char adj[10];
    float weight = 0;
    Node *next = nullptr;
};

struct Adj_list
{
    string head;
    float w = 0;
    Node* list = (Node *)malloc(sizeof(Node));
    Node *end = list;
};

class Graph
{
private:
    unordered_map<string , int> head;
    vector<float *>g;
    Adj_list ans[100];
    int sum = 0;
    int n = 0;
public:
    Graph(){;};
    int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)的查找
    void Create();
    void dfs(int pos , int end , float len , float *visit);
    void Find_min();
    void Flord();
    friend void Show(const vector<float *> &g , Adj_list *ans , int n);
};

void Show(const vector<float *> &g , Adj_list *ans , int n) {
    for(int i = 1;i <= n;i ++)
    {
        cout << ans[i].head << ' ';
        int p = 1;
        while(p <= n)
        {
            if(g[i][p] < maxx)cout << "----" << ans[p].head << "(" << g[i][p] << ") ";
            p ++;
        }
        cout << endl;
    }
}

void Graph::Create()
{
    ifstream file("CGraph.txt");
    if(file.fail())
    {
        cout << "文件打开失败";
        exit(0);
    }
    file >> n;
    for(int i = 0;i <= n;i ++)
    {
        auto *temp = (float *)malloc(sizeof(float) * n);
        for(int j = 1;j <= n;j ++)temp[j] = maxx;
        g.push_back(temp);
    }
    for(int i = 1;i <= n;i ++)
    {
        string temp;
        file >> temp;
        ans[i].head = temp;
        head.insert(make_pair(temp , i));
    }
    while(!file.eof())
    {
        string h , a;
        float data;
        file >> h >> a >> data;
        int p = Find_pos(h);
        int q = Find_pos(a);
        g[p][q] = data;
        sum ++;
    }
    file.close();
    cout << "创建的图为: " << endl;
    Show(g , ans , n);
}

void Graph::dfs(int pos , int end , float len , float *visit) {
    if(pos == end)
    {
        if(len < visit[end])visit[end] = len;
        return;
    }
    for(int i = 1;i <= n;i ++)
    {
        if(g[pos][i] < maxx)
        {
            if(len + g[pos][i] < visit[i])visit[i] = len + g[pos][i];
            dfs(i , end , len + g[pos][i] , visit);
        }
    }
}

void Graph::Find_min() {
    float visit[100] = {};
    for(int i = 1;i <= n;i ++)visit[i] = maxx;
    string start , end;
    cout << "请输入起始点和终止点: ";
    cin >> start >> end;
    int s = Find_pos(start);
    int e = Find_pos(end);
    dfs(s , e , 0 , visit);
    cout << start << "和" << end << "间的最短距离为: " << visit[e] << endl;
}

void Graph::Flord() {
    vector<float *> D;
    for(int i = 0;i <= n;i ++)
    {
        auto *temp = (float *)malloc(sizeof(float) * n);
        for(int j = 0;j <= n;j ++)
        {
            temp[j] = g[i][j];
        }
        D.push_back(temp);
    }
    for(int k = 1; k <= n;k ++)
    {
        for(int i = 1; i <= n;i ++)
            for(int j = 1; j <= n; j ++)
            {
                if(D[i][j] > D[i][k] + D[k][j]) D[i][j] = D[i][k] + D[k][j];
            }
    }
    for(int i = 1;i <= n;i ++)
    {
        for(int j = 1;j <= n;j ++)
        {
            if(D[i][j] < maxx)cout << i << "到" << j << "的最短路径为: " << D[i][j] << endl;
        }
    }
    for(int i = 0;i <= n;i ++)free(D[i]);
    D.clear();
}

int main()
{
    Graph graph;
    graph.Create();
    graph.Flord();
}












