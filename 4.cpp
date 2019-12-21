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

const int M = 3;//分成M类
const int N = 4;//数据有N维
#define max 65536;
struct Node
{
    double data[N]{};
    int num{};
    Node(){for(double & i : data)i = 0;};//默认构造函数
    Node(const Node &t){for(int i = 0;i < N;i ++)data[i] = t.data[i];num = t.num;};//重载构造函数
    bool operator==(Node &t){for(int i = 0;i < N;i ++){if(data[i] == t.data[i])continue;else return false;}return true;};//比较两个Node是否相等就是比较每个data元素是否相等
    friend istream&operator>>(istream &in , Node &t){for(double &i: t.data)in >> i;return in;};
};

class Cluster
{
private:
    vector<Node> ans;
    Node aver;
    Node pre_aver;
    bool check = false;
public:
    void Set(Node &t);//将平均值aver设置为t
    void New(Node &t);//在数组ans中加入t
    void Cal_aver();//计算ans中的平均值，同时将原本的平均值aver存到pre_aver中
    void Check();//查看N维向量是否都已经聚类，反应到check是否为true
    void Show(){for(const auto& x: ans)cout << x.num << ' ';};
    void Clear(){ans.clear();};//清除ans数组中的内容
    Node &Get_aver(){return aver;};//获取平均值
    int Getsize(){return ans.size();};//获取ans中元素的个数
    bool ok(){return check;};//获取check的值
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

double Cal_distance(Cluster &c , Node &t)//计算一个和一个聚类的中心点的欧氏距离
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
    int iteration_time = 0;//存储总的迭代次数
    ifstream file("Iris.txt");
    if(file.fail())
    {
        cout << "无法打开文件! "<< endl;
        exit(0);
    }
    istream_iterator<Node> it(file) , eof;//读入所有数据
    vector<Node> node(it , eof);//将数据存放到node数组中
    int signal = 1;
    int size = node.size();
    if(M > size)//要分的类数比原本数据样本数量多
    {
        cout << "样本数据不足! ";
        exit(0);
    }
    for(int i = 0;i < size; i ++)
    {
        node[i].num = signal;//给每一个node做标号
        signal ++;
    }
    Cluster Ans[M];//Ans数组中每一个元素为最后聚类的所有点
    for(int i = 0;i < M;i ++)
    {
        Ans[i].Set(node[i]);//先选取前M个点放入聚类中
    }
    while(true)
    {
        for(auto x: node)//对每一个点计算它和哪个聚类欧氏距离最近，离哪个最近就加入哪个
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
        for(auto & An : Ans)//一轮结束之后进行check
        {
            An.Cal_aver();
            An.Check();
        }
        if(is_ok(Ans))break;//所有聚类全部完成就可以返回
        iteration_time ++;//否则迭代次数+1
        for(auto & An : Ans)An.Clear();//清空Ans
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