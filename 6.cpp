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
const float D_max = 100000;

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

struct Prim_node
{
    string name;
    string add;
    float distance = D_max;
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
    void Prim();
    void Kruscal();
    void Clear_ans();
    friend void Show(Adj_list *g , int n);
};


void Show(Adj_list *g , int n) {
    for(int i = 1;i <= n;i ++)
    {
        cout << g[i].head << ' ';
        Node *p = g[i].list;
        p = p->next;
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
    cout << "创建的图为: " << endl;
    Show(g , n);
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
    cout << "Kruscal算法的结果为: " << endl;
    Show(ans , n);
}

void Graph::Prim() {
    Prim_node node[100];
    int count = 1;
    int pos = 1;
    int visit[100] = {};
    while(count < n)
    {
        Node *p = g[pos].list->next;
        visit[pos] = 1;
        while(p != nullptr)
        {
            int t = Find_pos(p->adj);
            if(!visit[t] && node[t].distance > p->weight)
            {
                node[t].name = g[pos].head;
                node[t].add = p->adj;
                node[t].distance = p->weight;
            }
            p = p->next;
        }
        float dis = D_max;
        for(int i = 1;i <= n;i ++)
        {
            if(!visit[i] && node[i].distance < dis)
            {
                dis = node[i].distance;
                pos = i;
            }
        }
        int m = Find_pos(node[pos].name);
        int m2 = Find_pos(node[pos].add);
        Node *temp = (Node *)malloc(sizeof(Node));
        Node *temp2 = (Node *)malloc(sizeof(Node));
        strcpy(temp->adj , node[pos].add.c_str());
        strcpy(temp2->adj , node[pos].name.c_str());
        temp->weight = temp2->weight = dis;
        temp->next = temp2->next = nullptr;
        ans[m].end->next = temp;
        ans[m].end = ans[m].end->next;
        ans[m2].end->next = temp2;
        ans[m2].end = ans[m2].end->next;
        count ++;
    }
    cout << "Prim算法的结果为: " << endl;
    Show(ans , n);
}

Node *Clear(Node *x) {
    if(x == nullptr)return nullptr;
    x->next = Clear(x->next);
    free(x);
    x = nullptr;
    return x;
}

void Graph::Clear_ans() {
    for(int i = 1;i <= n;i ++)
    {
        ans[i].list->next = Clear(ans[i].list->next);
        ans[i].end = ans[i].list;
    }
}

int main()
{
    Graph graph;
    graph.Create();
    graph.Kruscal();
    graph.Clear_ans();
    graph.Prim();
}







