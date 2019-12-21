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

struct Node//�ڽӱ�ڵ�
{
    char adj[10]{};//�ڽӵ������
    float weight = 0;//�ߵ�Ȩֵ
    Node *next = nullptr;//��һ����
};

struct Adj_list//�ڽӱ�ͷ�ڵ�
{
    string head;//ͷ�ڵ�����
    Node* list = (Node *)malloc(sizeof(Node));//�ڽӱ�
    Node *end = list;//β�ڵ��λ��
};

struct node//Kruscal�㷨�Ľڵ����ݽṹ
{
    string p;
    string q;//���˵Ľڵ���
    float weight = 0;//�ߵ�Ȩֵ
    friend bool operator>(const node &a , const node &b){return a.weight > b.weight;};//���ش��ںţ���������
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
    unordered_map<string , int> head;//�ڵ����ƺͽڵ���ŵ�ӳ�伯��
    Adj_list g[100];//ԭʼͼ
    Adj_list ans[100];//�õ�����С������ͼ
    priority_queue<node , vector<node> , greater<> > min_e;//�����ȶ��У�ȨֵС�ı���ǰ
    int sum = 0;//������
    int n = 0;//�ڽӱ����
public:
    Graph(){;};//Ĭ�Ϲ��캯��
    int Find_pos(const string &name){auto x = head.find(name);return x->second;};//O(1)�Ĳ���
    void Create();//����ͼ
    void Prim();//Prim�㷨
    void Kruscal();//Kruscal�㷨
    void Clear_ans();//���ͼans��������õ�����С������
    friend void Show(Adj_list *g , int n);//���ͼ
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
        cout << "�ļ���ʧ��";
        exit(0);
    }
    file >> n;
    for(int i = 1;i <= n;i ++)//��ȡ���ж�����Ϣ���Զ�����б��
    {
        string temp;
        file >> temp;
        g[i].head = temp;
        g[i].list->next = nullptr;
        ans[i].head = temp;
        head.insert(make_pair(temp , i));//�����������ͱ�ŵ�ӳ��
    }
    while(!file.eof())
    {
        string h , a;
        float data;
        file >> h >> a >> data;//���붥��ͱߵ���Ϣ
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
        g[pos].end = g[pos].end->next;//��Ϊ������ͼ����Ҫ���ڽӱ��ڶ������㶼������
        sum ++;
        node t{h , a , data};
        min_e.push(t);
    }
    file.close();
    cout << "������ͼΪ: " << endl;
    Show(g , n);
}

void Graph::Kruscal() {
    int use[100];//���һ�����һ����ͨ��֧�ڹ����б�������������ô�����е��use��ɱ����С����һ��
    for(int i = 1;i <= n;i ++)use[i] = i;//���use������ֵӦ�ö���1
    int count = 1;//count-1��ʾ��ǰ�ı���
    while(count < n)
    {
        node t = min_e.top();//ȡ����Ȩֵ��С��
        min_e.pop();
        int p_pos = Find_pos(t.p);
        int q_pos = Find_pos(t.q);
        if(use[p_pos] != use[q_pos])//use��Ų�ͬ����ʾ����������ͨ��֧�󲻻ṹ�ɻ�·
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
            for(int i = 1;i <= n;i ++)if(use[i] == max)use[i] = min;//��������use�ı��
            count ++;
        }
    }
    cout << "Kruscal�㷨�Ľ��Ϊ: " << endl;
    Show(ans , n);
}

void Graph::Prim() {
    Prim_node node[100];//node��ʾ��ǰ����ͨ��֧�����Ӧ�ĵ���̾����Ƕ���
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
        for(int i = 1;i <= n;i ++)//�ҵ�Ȩֵ��С�ı�
        {
            if(!visit[i] && node[i].distance < dis)
            {
                dis = node[i].distance;
                pos = i;
            }
        }//������������ͨ��֧
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
    cout << "Prim�㷨�Ľ��Ϊ: " << endl;
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