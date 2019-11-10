//
// Created by haoha on 2019/11/10.
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

struct CPath
{
    int pos = 0;
    float max = 0;
    float min = maxx;
    float a = maxx;
};

template <typename T>
T Max(const T &a , const T &b)
{
    if(a > b)return a;
    return b;
}

template <typename T>
T Min(const T &a , const T &b)
{
    if(a > b)return b;
    return a;
}

class Graph
{
private:
    unordered_map<string , int> head;
    Adj_list g[100];
    Adj_list ans[100];
    vector<CPath> path;
    vector<int> TP;
    int sum = 0;//边总数
    int n = 0;//邻接表个数
public:
    Graph(){;};
    int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)的查找
    int Find(const int &t){for(int i = 0;i < TP.size();i ++)if(TP[i] == t)return i;};
    void Create();
    bool TPsort();
    void Ans();
    float dfs(int i);
    friend void Show(Adj_list *g , int n);
};

void Show(Adj_list *g , int n) {
    for(int i = 1;i <= n;i ++)
    {
        cout << g[i].head << ' ';
        Node *p = g[i].list->next;
        while(p != nullptr)
        {
            cout << "----" << p->adj << "(" << p->weight << ") ";
            p = p->next;
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
    for(int i = 1;i <= n;i ++)
    {
        string temp;
        file >> temp;
        g[i].head = temp;
        g[i].list->next = nullptr;
        ans[i].head = temp;
        head.insert(make_pair(temp , i));
    }
    while(!file.eof())
    {
        string h , a;
        float data;
        file >> h >> a >> data;
        int pos = Find_pos(h);
        Node *temp = (Node *)malloc(sizeof(Node));
        strcpy(temp->adj , a.c_str());
        temp->weight = data;
        temp->next = nullptr;
        g[pos].end->next = temp;
        g[pos].end = g[pos].end->next;
        sum ++;
    }
    file.close();
    cout << "创建的图为: " << endl;
    Show(g , n);
}

bool Graph::TPsort() {
    stack<int> s;
    int count = 0;
    int In[100] = {};
    for(int i = 1;i <= n;i ++)
    {
        Node *p = g[i].list->next;
        while(p != nullptr)
        {
            int pos = Find_pos(p->adj);
            In[pos] ++;
            p = p->next;
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        if(!In[i])
        {
            s.push(i);
            TP.push_back(i);
            CPath temp;
            temp.pos = i;
            g[i].w = 0;
            path.push_back(temp);
            break;
        }
    }
    while(!s.empty())
    {
        int top = s.top();
        s.pop();
        count ++;
        Node *p = g[top].list->next;
        while(p != nullptr)
        {
            int pos = Find_pos(p->adj);
            g[pos].w = Max<float>(g[top].w + p->weight , g[pos].w);
            In[pos] --;
            if(!In[pos])
            {
                s.push(pos);
                TP.push_back(pos);
                CPath temp;
                temp.pos = pos;
                temp.max = g[pos].w;
                path.push_back(temp);
            }
            p = p->next;
        }
    }
    return count == n;
}

float Graph::dfs(int i) {//i表示的是拓扑排序中点的位置，即T[i]才是点
    if(i == TP.size() - 1)
    {
        path[i].min = path[i].max;
        return path[i].max;
    }
    Node *p = g[TP[i]].list->next;
    while(p != nullptr)
    {
        int pos = Find_pos(p->adj);
        float temp = dfs(Find(pos)) - p->weight;
        path[i].min = Min<float>(temp , path[i].min);
        p = p->next;
    }
    return path[i].min;
}

void Graph::Ans() {
    dfs(TP , 0 , 0);
    for(auto &x: path)
    {
        x.a = x.max - x.min;
        if(x.a == 0)cout << x.pos << ' ';
    }
}


int main()
{
    Graph graph;
    graph.Create();
    if(graph.TPsort())cout << "拓扑排序成功" << endl;
    else cout << "拓扑排序失败" << endl;
    graph.Ans();
}









