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

struct Node//�ڽӱ�ڵ�
{
    char adj[10];
    float weight = 0;
    Node *next = nullptr;
};

struct Adj_list//�ڽӱ�ͷ�ڵ�
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

template <typename T>//ģ�����ֵ
T Max(const T &a , const T &b)
{
    if(a > b)return a;
    return b;
}

template <typename T>//ģ����Сֵ
T Min(const T &a , const T &b)
{
    if(a > b)return b;
    return a;
}

class Graph
{
private:
    unordered_map<string , int> head;//�ڵ����ƺͽڵ���ŵ�ӳ�伯��
    Adj_list g[100];//ԭʼͼ
    Adj_list ans[100];
    vector<CPath> path;//ÿ��������ʼʱ����������ʱ��
    vector<int> TP;//���������˳��
    int sum = 0;//������
    int n = 0;//�ڽӱ����
public:
    Graph(){;};
    int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)�Ĳ���
    int Find(const int &t){for(int i = 0;i < TP.size();i ++)if(TP[i] == t)return i;return TP.size();};//������������Ѱ��t
    void Create();//����ͼ
    bool TPsort();//��������
    void Ans();//��ʾ���
    float dfs(int i);//dfs
    friend void Show(Adj_list *g , int n);//��ʾͼ
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
        cout << "�ļ���ʧ��";
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
    cout << "������ͼΪ: " << endl;
    Show(g , n);
}

bool Graph::TPsort() {
    stack<int> s;
    int count = 0;
    int In[100] = {};//�洢���е�����
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
        if(!In[i])//���Ϊ0
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

float Graph::dfs(int i) {//i��ʾ�������������е��λ�ã���T[i]���ǵ�
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
        x.a = x.max - x.min;
        if(x.a == 0)cout << x.pos << ' ';
    }
}


int main()
{
    Graph graph;
    graph.Create();
    if(graph.TPsort())cout << "��������ɹ�" << endl;
    else cout << "��������ʧ��" << endl;
    graph.Ans();
}









