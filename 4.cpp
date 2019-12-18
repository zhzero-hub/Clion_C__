//
// Created by haoha on 2019/10/10.
//

#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

const int M = 3;
const int N = 4;
#define max 65536;
struct Node
{
    double data[N]{};
    int num{};
    Node();
    Node(const Node &t){for(int i = 0;i < N;i ++)data[i] = t.data[i];num = t.num;};
    bool operator==(Node &t){for(int i = 0;i < N;i ++){if(data[i] == t.data[i])continue;else return false;}return true;};
    friend istream&operator>>(istream &in , Node &t){for(double & i : t.data)in >> i;return in;};
};

Node::Node() {for(double & i : data)i = 0;}

class Cluster
{
private:
    vector<Node> ans;
    Node aver;
    Node pre_aver;
    bool check = false;
public:
    void Set(Node &t);
    void New(Node &t);
    void Cal_aver();
    void Check();
    void Show(){for(const auto& x: ans)cout << x.num << ' ';};
    void Clear(){ans.clear();};
    Node &Get_aver(){return aver;};
    int Getsize(){return ans.size();};
    bool ok(){return check;};
};

void Cluster::Set(Node &t)
{
    aver = t;
}

void Cluster::New(Node &t)
{
    ans.push_back(t);
}

void Cluster::Cal_aver()
{
    Node temp;
    int count = 0;
    for(const auto& x: ans)
    {
        for(int i = 0;i < N;i ++)temp.data[i] += x.data[i];
        count ++;
    }
    pre_aver = aver;
    for(int i = 0;i < N;i ++)aver.data[i] = temp.data[i] / count;
}

void Cluster::Check()
{
    double ch[N];
    int c = 0;
    for(int i = 0;i < N;i ++)
    {
        ch[i] = aver.data[i] - pre_aver.data[i];
        if(ch[i] < 0.00001 && ch[i] > -0.00001)continue;
        else c ++;
    }
    check = c == 0;
}

double Cal_distance(Cluster &c , Node &t)
{
    Node center = c.Get_aver();
    double temp[N];
    for(int i = 0;i < N;i ++)temp[i] = center.data[i] - t.data[i];
    double sum = 0;
    for(double i : temp)sum = sum + i * i;
    return sqrt(sum);
}

bool is_ok(Cluster Ans[])
{
    for(int i = 0;i < M;i ++)
    {
        if(Ans[i].ok())continue;
        else return false;
    }
    return true;
}

int main()
{
    int iteration_time = 0;
    ifstream file("Iris.txt");
    if(file.fail())
    {
        cout << "无法打开文件! "<< endl;
        exit(0);
    }
    istream_iterator<Node> it(file) , eof;
    vector<Node> node(it , eof);
    int signal = 1;
    int size = node.size();
    if(M > size)
    {
        cout << "样本数据不足! ";
        exit(0);
    }
    for(int i = 0;i < size; i ++)
    {
        node[i].num = signal;
        signal ++;
    }
    Cluster Ans[M];
    for(int i = 0;i < M;i ++)
    {
        Ans[i].Set(node[i]);
    }
    while(true)
    {
        for(auto x: node)
        {
            double dis_min = max;
            int pos = 0;
            for(int i = 0;i < M;i ++)
            {
                double temp_dis = Cal_distance(Ans[i] , x);
                if(temp_dis < dis_min)
                {
                    dis_min = temp_dis;
                    pos = i;
                }
            }
            Ans[pos].New(x);
        }
        for(auto & An : Ans)
        {
            An.Cal_aver();
            An.Check();
        }
        if(is_ok(Ans))break;
        iteration_time ++;
        for(auto & An : Ans)An.Clear();
    }
    cout << "迭代次数为: " << iteration_time << endl;
    for(int i = 0;i < M;i ++)
    {
        cout << "第" << i + 1 << "聚类的点的序号为: ";
        Ans[i].Show();
        cout << endl;
        cout << "共" << Ans[i].Getsize()  << "个点" << endl;
    }
}