//
// Created by Z_HAO on 2019/12/27.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int M = 3;

struct Node
{
    vector<pair<Node * , int>> data;
    Node *end = nullptr;
};

unsigned long long int ceil(unsigned long long int x)//[x/2]����ȡ��
{
    return (x - 1) / 2 + 1;
}

unsigned long long int Binary_search(const vector<pair<Node * , int>> &x , const int &t , unsigned long long int l , unsigned long long int r)//O(log(x.size()))
{//���ֲ��ң�ֻȷ����Χ������һ����t��������������������С�ڵ��������±���������һ��������Ǵ�������Ԫ�أ��������һ��Ԫ�ص��±�
    if(l == r)
    {
        return l;
    }
    unsigned long long int mid = (l + r) / 2;
    unsigned int ret = 0;
    if(t < x[mid].second)
    {
        ret = Binary_search(x , t , l , mid);
    }
    else if(t > x[mid].second)
    {
        ret = Binary_search(x , t , mid + 1, r);
    }
    else if(t == x[mid].second)
    {
        return mid;
    }
    return ret;
}

void Show(Node *x)
{
    if(x == nullptr)return;
    for(const auto &y: x->data)
    {
        cout << y.second << ' ';
    }
    for(const auto &y: x->data)
    {
        Show(y.first);
    }
    Show(x->end);
}

Node *Insert(Node *x , const int &t , pair<Node * , int> &up , int layer)
{
    if(x == nullptr)
    {
        Node *base = new Node;
        base->end = nullptr;
        base->data.emplace_back(nullptr , t);
        return base;
    }
    unsigned long long int pos = Binary_search(x->data , t , 0 , x->data.size() - 1);//���ֲ���
    if(x->data[pos].second == t)//�����Ѿ������ֵ��ֱ�ӷ���
    {
        return x;
    }
    if(x->end == nullptr)//���һ��
    {
        if(t > x->data[pos].second)pos ++;//��������������е�Ԫ�أ�����뵽���
        x->data.insert(x->data.begin() + pos , make_pair(nullptr , t));
    }
    else {
        if(t < x->data[pos].second)
        {
            x->data[pos].first = Insert(x->data[pos].first , t , up , layer + 1);//�ݹ����
        }
        else if(t > x->data[pos].second)
        {
            x->end = Insert(x->end , t , up , layer + 1);
        }
    }
    if(up.first != nullptr)//�鿴�Ƿ���Ҫ��������Ԫ��
    {
        if(up.second > x->data[pos].second)pos ++;
        x->data.insert(x->data.begin() + pos , up);
        up.first = nullptr;
    }
    if(x->data.size() == M)//���϶�
    {
        int mid = M / 2;
        if(layer == 0)//���ڵ����
        {
            Node *base = new Node;
            Node *l = new Node;
            Node *r = new Node;
            base->end = l->end = r->end = nullptr;
            base->data.emplace_back(l , x->data[mid].second);
            base->end = r;
            copy(x->data.begin() , x->data.begin() + mid , insert_iterator<vector<pair<Node * , int>>>(l->data , l->data.end()));
            l->end = x->data[mid].first;
            copy(x->data.begin() + mid + 1 , x->data.end() , insert_iterator<vector<pair<Node * , int>>>(r->data , r->data.end()));
            r->end = x->end;
            delete x;
            up.first = nullptr;
            return base;
        }
        Node *node = new Node;
        copy(x->data.begin() , x->data.begin() + mid , insert_iterator<vector<pair<Node * , int>>>(node->data , node->data.end()));
        auto it = x->data.erase(x->data.begin() , x->data.begin() + mid);
        up.first = node;
        node->end = it->first;
        up.second = it->second;
        x->data.erase(x->data.begin());
    }
    return x;
}

bool Find(Node *x , const int &t)
{
    unsigned long long int pos = Binary_search(x->data , t , 0 , x->data.size() - 1);
    if(x->data[pos].second == t)
    {
        return true;
    }
    if(x->end == nullptr)
    {
        return false;
    }
    else
    {
        if(t > x->data[pos].second)
        {
            return Find(x->end , t);
        }
        return Find(x->data[pos].first , t);
    }
}

Node *Delete(Node *x , const int &t , int &flag)
{
    unsigned long long int pos = Binary_search(x->data , t , 0 , x->data.size() - 1);
    if(x->data[pos].second == t)
    {
        if(x->end == nullptr)//ɾ������Ҷ�ڵ�
        {
            x->data.erase(x->data.begin() + pos);
        }
        else {//��Ҷ�ڵ�
            // ���ý��Ϊ��Ҷ��㣬�ұ�ɾ�ؼ���Ϊ�ý���е�i���ؼ���key[i]����ɴ�ָ��son[i]��ָ���������ҳ���С�ؼ���Y������key[i]��λ�ã�Ȼ����Ҷ�����ɾȥY

        }
    }
    else if(x->end == nullptr)
    {
        cout << "δ�ҵ��ýڵ�" << endl;
    }
    else {
        if(t > x->data[pos].second)
        {
            x->end = Delete(x->end , t , flag);
        }
        else {
            x->data[pos].first = Delete(x->data[pos].first , t , flag);
        }
    }
    int size = x->data.size();
    if(!flag)
    {
        if(pos == 0)
        {
            if(size == 1)//ֻ���ܳ�����M=3��ʱ��
            {
                if(!x->end && x->end->data.size() >= ceil(M))
                {
                    x->data[0].first->data.emplace_back(nullptr , x->data[0].second);
                    x->data[0].second = x->end->data[0].second;
                    x->end->data.erase(x->end->data.begin());
                    flag = 0;
                    return x;
                }
            }
            else {//0��λֻ�����ֵ�
                if(!x->data[pos + 1].first && x->data[pos + 1].first->data.size() >= ceil(M))
                {
                    x->data[pos + 1].first->data.emplace_back(nullptr , x->data[pos + 1].second);
                    x->data[pos + 1].second = x->data[pos + 1].first->data[0].second;
                    x->data[pos + 1].first->data.erase(x->end->data.begin());
                    flag = 0;
                    return x;
                }
            }
        }
        else if(pos == size - 1)//ֻ�����ֵ�
        {
            if(t > x->data[pos].second)//endɾ��
            {
                if(!x->data[pos].first && x->data[pos].first->data.size() >= ceil(M))//�鿴�����ڶ����Ƿ���Զ���ȥ
                {//���ԵĻ������һ������ȥ
                    x->end->data.emplace_back(nullptr , x->data[pos].second);
                    x->data[pos].second = x->data[pos].first->data[x->data[pos].first->data.size() - 1].second;
                    x->data[pos].first->data.pop_back();
                    flag = 0;
                    return x;
                }
            }
        }
        else {//���Ҷ����ֵ�
            if(!x->data[pos + 1].first && x->data[pos + 1].first->data.size() >= ceil(M))
            {
                x->data[pos + 1].first->data.emplace_back(nullptr , x->data[pos + 1].second);
                x->data[pos + 1].second = x->data[pos + 1].first->data[0].second;
                x->data[pos + 1].first->data.erase(x->end->data.begin());
                flag = 0;
                return x;
            }
            else if(!x->data[pos - 1].first && x->data[pos - 1].first->data.size() >= ceil(M))
            {
                x->data[pos - 1].first->data.emplace_back(nullptr , x->data[pos - 1].second);
                x->data[pos - 1].second = x->data[pos - 1].first->data[x->data[pos - 1].first->data.size() - 1].second;
                x->data[pos - 1].first->data.pop_back();
                flag = 0;
                return x;
            }
        }
    }
    if(!flag)//�����ֵ�û�п��Ի��Ľڵ�
    {
        if(pos == size)
        {

        }
    }
    //�����ж��Ƿ�������
    if(x->data.size() < ceil(M) - 1)//����
    {
        flag = 1;
    }
    return x;
}

int main()
{
    Node *base = nullptr;
    pair<Node * , int> up;
    up.first = nullptr;
    for(int i = 0;i < 100;i ++)
    {
        base = Insert(base , rand() % 100 , up , 0);
    }
    Show(base);
    cout << endl;

    cout << "Succeed! " << endl;
}
















