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

const int M = 3;//�ֳ�M��
const int N = 4;//������Nά
#define max 65536;
struct Node
{
    double data[N]{};
    int num{};
    Node(){for(double & i : data)i = 0;};//Ĭ�Ϲ��캯��
    Node(const Node &t){for(int i = 0;i < N;i ++)data[i] = t.data[i];num = t.num;};//���ع��캯��
    bool operator==(Node &t){for(int i = 0;i < N;i ++){if(data[i] == t.data[i])continue;else return false;}return true;};//�Ƚ�����Node�Ƿ���Ⱦ��ǱȽ�ÿ��dataԪ���Ƿ����
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
    void Set(Node &t);//��ƽ��ֵaver����Ϊt
    void New(Node &t);//������ans�м���t
    void Cal_aver();//����ans�е�ƽ��ֵ��ͬʱ��ԭ����ƽ��ֵaver�浽pre_aver��
    void Check();//�鿴Nά�����Ƿ��Ѿ����࣬��Ӧ��check�Ƿ�Ϊtrue
    void Show(){for(const auto& x: ans)cout << x.num << ' ';};
    void Clear(){ans.clear();};//���ans�����е�����
    Node &Get_aver(){return aver;};//��ȡƽ��ֵ
    int Getsize(){return ans.size();};//��ȡans��Ԫ�صĸ���
    bool ok(){return check;};//��ȡcheck��ֵ
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

double Cal_distance(Cluster &c , Node &t)//����һ����һ����������ĵ��ŷ�Ͼ���
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
    int iteration_time = 0;//�洢�ܵĵ�������
    ifstream file("Iris.txt");
    if(file.fail())
    {
        cout << "�޷����ļ�! "<< endl;
        exit(0);
    }
    istream_iterator<Node> it(file) , eof;//������������
    vector<Node> node(it , eof);//�����ݴ�ŵ�node������
    int signal = 1;
    int size = node.size();
    if(M > size)//Ҫ�ֵ�������ԭ����������������
    {
        cout << "�������ݲ���! ";
        exit(0);
    }
    for(int i = 0;i < size; i ++)
    {
        node[i].num = signal;//��ÿһ��node�����
        signal ++;
    }
    Cluster Ans[M];//Ans������ÿһ��Ԫ��Ϊ����������е�
    for(int i = 0;i < M;i ++)
    {
        Ans[i].Set(node[i]);//��ѡȡǰM������������
    }
    while(true)
    {
        for(auto x: node)//��ÿһ������������ĸ�����ŷ�Ͼ�����������ĸ�����ͼ����ĸ�
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
        for(auto & An : Ans)//һ�ֽ���֮�����check
        {
            An.Cal_aver();
            An.Check();
        }
        if(is_ok(Ans))break;//���о���ȫ����ɾͿ��Է���
        iteration_time ++;//�����������+1
        for(auto & An : Ans)An.Clear();//���Ans
    }
    cout << "��������Ϊ: " << iteration_time << endl;
    for(int i = 0;i < M;i ++)
    {
        cout << "��" << i + 1 << "����ĵ�����Ϊ: ";
        Ans[i].Show();
        cout << endl;
        cout << "��" << Ans[i].Getsize()  << "����" << endl;
    }
}