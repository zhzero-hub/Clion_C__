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
    char adj[10]{};//邻接点的名称
    float weight = 0;//边的权值
    Node *next = nullptr;//下一个点
};

struct Adj_list//邻接表头节点
{
    string head;//头节点名称
    Node* list = (Node *)malloc(sizeof(Node));//邻接表
    Node *end = list;//尾节点的位置
};

struct node//Kruscal算法的节点数据结构
{
    string p;
    string q;//两端的节点名
    float weight = 0;//边的权值
    friend bool operator>(const node &a , const node &b){return a.weight > b.weight;};//重载大于号，用于排序
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
    unordered_map<string , int> head;//节点名称和节点序号的映射集合
    Adj_list g[100];//原始图
    Adj_list ans[100];//得到的最小生成树图
    priority_queue<node , vector<node> , greater<> > min_e;//边优先队列，权值小的边在前
    int sum = 0;//边总数
    int n = 0;//邻接表个数
public:
    Graph(){;};//默认构造函数
    int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)的查找
    void Create();//创建图
    void Prim();//Prim算法
    void Kruscal();//Kruscal算法
    void Clear_ans();//清楚图ans，即清除得到的最小生成树
    friend void Show(Adj_list *g , int n);//输出图
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
    for(int i = 1;i <= n;i ++)//读取所有顶点信息并对顶点进行标号
    {
        string temp;
        file >> temp;
        g[i].head = temp;
        g[i].list->next = nullptr;
        ans[i].head = temp;
        head.insert(make_pair(temp , i));//构建顶点名和标号的映射
    }
    while(!file.eof())
    {
        string h , a;
        float data;
        file >> h >> a >> data;//读入顶点和边的信息
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
        g[pos].end = g[pos].end->next;//因为是无向图，需要在邻接表内对两个点都做处理
        sum ++;
        node t{h , a , data};
        min_e.push(t);
    }
    file.close();
    cout << "创建的图为: " << endl;
    Show(g , n);
}

void Graph::Kruscal() {
    int use[100];//如果一个点和一个连通分支在过程中被连了起来，那么将所有点的use设成标号最小的那一个
    for(int i = 1;i <= n;i ++)use[i] = i;//最后use的所有值应该都是1
    int count = 1;//count-1表示当前的边数
    while(count < n)
    {
        node t = min_e.top();//取出边权值最小的
        min_e.pop();
        int p_pos = Find_pos(t.p);
        int q_pos = Find_pos(t.q);
        if(use[p_pos] != use[q_pos])//use标号不同，表示这个点加入连通分支后不会构成回路
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
            for(int i = 1;i <= n;i ++)if(use[i] == max)use[i] = min;//重新设置use的标号
            count ++;
        }
    }
    cout << "Kruscal算法的结果为: " << endl;
    Show(ans , n);
}

void Graph::Prim() {
    Prim_node node[100];//node表示当前的连通分支中离对应的点最短距离是多少
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
        for(int i = 1;i <= n;i ++)//找到权值最小的边
        {
            if(!visit[i] && node[i].distance < dis)
            {
                dis = node[i].distance;
                pos = i;
            }
        }//将这个点加入连通分支
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