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

struct Adj_list//邻接表头节点
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

template <typename T>//模板最大值
T Max(const T &a , const T &b)
{
    if(a > b)return a;
    return b;
}

template <typename T>//模板最小值
T Min(const T &a , const T &b)
{
    if(a > b)return b;
    return a;
}

class Graph
{
private:
    unordered_map<string , int> head;//节点名称和节点序号的映射集合
    Adj_list g[100];//原始图
    Adj_list ans[100];
    vector<CPath> path;//每个点最晚开始时间和最早结束时间
    vector<int> TP;//拓扑排序的顺序
    int sum = 0;//边总数
    int n = 0;//邻接表个数
public:
    Graph(){;};
    int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)的查找
    int Find(const int &t){for(int i = 0;i < TP.size();i ++)if(TP[i] == t)return i;return TP.size();};//在拓扑排序中寻找t
    void Create();//创建图
    bool TPsort();//拓扑排序
    void Ans();//显示结果
    float dfs(int i);//dfs
    friend void Show(Adj_list *g , int n);//显示图
    void Print_ans(Adj_list *ans , int *visit , vector<pair<CPath , char *>> &pa);//输出关键路径函数，用于dfs
    void Print();//输出关键路径函数，用于初始化
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
    int In[100] = {};//存储所有点的入度
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
        if(!In[i])//入度为0
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
    return count == n;//只有count等于n表示所有点都在拓扑排序中，拓扑排序成功才能找到关键路径
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
    dfs(0);
    for(auto &x: path)
    {
        x.a = x.min - x.max;
    }
    cout << "顶点: \t\t";
    for(const auto &x: path)printf("%4d " , x.pos);
    cout << endl;
    cout << "最早开始时间:\t ";
    for(const auto &x: path)printf("%4.1f " , x.max);
    cout << endl;
    cout << "最晚开始时间:\t ";
    for(const auto &x: path)printf("%4.1f " , x.min);
    cout << endl;
    cout << "差值: \t\t";
    for(const auto &x: path)printf("%4.1f " , x.a);;
    cout << endl;
}

void Graph::Print_ans(Adj_list *a , int *visit , vector<pair<CPath , char *>> &pa) {
    Node *p = a->list->next;
    int i = Find_pos(a->head);//i是结点的标号
    if(i == TP[TP.size() - 1])
    {
        for(const auto &x: pa)
        {
            if(x.first.a != 0)return;//关键路径满足所有点的差值为0
        }
        unsigned int size = pa.size() - 1;
        for(unsigned int k = 0;k < size;k ++)cout << pa[k].second << "--->";
        cout << pa[size].second << endl;
    }
    while(p != nullptr)
    {
        i = Find_pos(p->adj);
        if(!visit[i])
        {
            visit[i] = 1;
            int j = Find(i);
            pa.emplace_back(path[j] , p->adj);
            Print_ans(&g[i] , visit , pa);
            visit[i] = 0;
            pa.pop_back();
        }
        p = p->next;
    }
}

void Graph::Print() {
    int visit[10010] = {};
    vector<pair<CPath , char *>> pa;
    char ch[100];
    strcpy(ch , g[TP[0]].head.c_str());
    pa.emplace_back(path[0] , ch);
    visit[TP[0]] = 1;
    Print_ans(&g[TP[0]] , visit , pa);
}


int main()
{
    Graph graph;
    graph.Create();
    if(graph.TPsort())cout << "拓扑排序成功" << endl;
    else {
        cout << "拓扑排序失败" << endl;
        return 0;
    }
    graph.Ans();
    cout << "关键路径为: " << endl;
    graph.Print();
}









