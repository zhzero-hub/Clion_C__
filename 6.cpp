//
// Created by haoha on 2019/10/21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <cstring>
#include <unordered_map>
using namespace std;

struct Node//邻接表节点
{
    char adj[10];
    float weight = 0;
    Node *next = nullptr;
};

struct Adj_list
{
    string head;
    Node* list = (Node *)malloc(sizeof(Node));
    Node *end = list;
};

struct node
{
    string p;
    string q;
    float weight = 0;
    friend bool operator>(const node &a , const node &b){return a.weight > b.weight;};
};

class Graph
{
private:
    unordered_map<string , int> head;
    Adj_list g[100];
    Adj_list ans[100];
    priority_queue<node , vector<node> , greater<> > min_e;
    int sum = 0;//边总数
    int n = 0;//邻接表个数
public:
        Graph(){;};
        int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)的查找
        void Create();
        void Kruscal();
        void Show();
};

void Graph::Create()
{
    ifstream file("Graph.txt");
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
        pos = Find_pos(a);
        temp = (Node *)malloc(sizeof(Node));
        strcpy(temp->adj , a.c_str());
        temp->weight = data;
        temp->next = nullptr;
        g[pos].end->next = temp;
        g[pos].end = g[pos].end->next;
        sum ++;
        node t{h , a , data};
        min_e.push(t);
    }
    file.close();
}

void Graph::Show() {
    for(int i = 1;i <= n;i ++)
    {
        cout << g[i].head << ' ';
        Node *p = g[i].list;
        p = p->next;
        while(p != nullptr)
        {
            cout << "-" << p->weight << "->" << p->adj << ' ';
            p = p->next;
        }
        cout << endl;
    }
}

void Graph::Kruscal() {
    int use[100];
    for(int i = 1;i <= n;i ++)use[i] = i;
    int count = 1;
    while(count < n)
    {
        node t = min_e.top();
        min_e.pop();
        int p_pos = Find_pos(t.p);
        int q_pos = Find_pos(t.q);
        if(use[p_pos] != use[q_pos])
        {
            Node *temp = (Node *)malloc(sizeof(Node));
            strcpy(temp->adj , t.q.c_str());
            temp->weight = t.weight;
            temp->next = nullptr;
            ans[p_pos].end->next = temp;
            ans[p_pos].end = ans[p_pos].end->next;
            temp = (Node *)malloc(sizeof(Node));
            strcpy(temp->adj , t.p.c_str());
            temp->weight = t.weight;
            temp->next = nullptr;
            ans[q_pos].end->next = temp;
            ans[q_pos].end = ans[q_pos].end->next;
            int min = p_pos;
            int max = q_pos;
            if(q_pos < min)
            {
                min = q_pos;
                max = p_pos;
            }
            for(int i = 1;i <= n;i ++)if(use[i] == max)use[i] = min;
            count ++;
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        cout << g[i].head << ' ';
        Node *p = ans[i].list;
        p = p->next;
        while(p != nullptr)
        {
            cout << "--" << p->weight << "-->" << p->adj;
            p = p->next;
        }
        cout << endl;
    }
}


int main()
{
    Graph graph;
    graph.Create();
    graph.Kruscal();
}







