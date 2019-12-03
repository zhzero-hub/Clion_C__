//
// Created by Z_HAO on 2019/11/28.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

int Find(const vector<pair<string , string>> &x , const string& t , int pos = 0)//��pos��ʼ��t
{
    int size = x.size();
    for(int i = pos;i < size;i ++)if(x[i].first == t)return i;
    return size;
}

int to_int(const string &x)
{
    int ans = 0;
    int i = 0;
    while(x[i] >= '0' && x[i] <= '9')
    {
        ans *= 10;
        ans += x[i] - '0';
        i ++;
    }
    return ans;
}

void Find_union(set<string> a , set<string> b , set<string> &c , vector<string> &ch)
{
    set_intersection(a.begin() , a.end() , b.begin() , b.end() , insert_iterator<set<string>>(c , c.end()));
    if(c.empty())
    {
        
    }
}

void bfs(vector<pair<string , vector<pair<string , string>>>> &stop , unordered_map<string , int> &number , queue<pair<string , string>> &q , string &end , int *visit , unordered_map<string , pair<string , string>> &ret)
{
    auto x = q.front();
    q.pop();
    cout << x.second << endl;
    if(x.second == end) {
        string t = x.second;
        vector<pair<string , string>> path;
        while(ret.find(t) != ret.end())
        {
            auto y = ret.find(t)->second;
            path.insert(path.begin() , y);
            t = y.second;
        }
        for(const auto &y: path)cout << "(" << y.first << ")" << y.second << ' ';
        cout << "(" << x.first << ")" << end << endl;
        return;
    }
    int pos = number.find(x.second)->second;
    int p = Find(stop[pos].second , x.first);
    while(p != stop[pos].second.size())
    {
        string temp = stop[pos].second[p].second;
        if(!visit[number.find(temp)->second])
        {
            visit[number.find(temp)->second] = 1;
            q.push(stop[pos].second[p]);
            ret.insert(make_pair(temp , x));
        }
        p = Find(stop[pos].second , x.first , p + 1);
    }
    for(const auto &y: stop[pos].second) {
        string temp = y.second;
        if (!visit[number.find(temp)->second]) {
            visit[number.find(temp)->second] = 1;
            q.push(y);
            ret.insert(make_pair(y.second , x));
        }
    }
    bfs(stop , number , q , end , visit , ret);
}

int main()
{
    unordered_map<string , int> number;
    unordered_map<string , set<string>> bus;
    vector<pair<string , vector<pair<string , string>>>> stop(5130);//5127????
    ifstream file("Bus.txt");
    if(file.fail())
    {
        cout << "�ļ�������! "<< endl;
        exit(0);
    }
    int i = 0;
    while(!file.eof())
    {
        string name;
        file >> name;
        int pos1 = -1 , pos2 = -1;
        string temp;
        file >> temp;
        int l = 0;
        int r = temp.find(',');
        string sub1 = temp.substr(l , r - l);
        if(number.find(sub1) == number.end())
        {
            stop[i].first = sub1;
            number.insert(make_pair(sub1 , i));
            pos1 = i;
            i ++;
        }
        else pos1 = number.find(sub1)->second;
        l = r + 1;
        r = temp.find(',' , r + 1);
        string sub2;
        if(r == std::__cxx11::string::npos)sub2 = temp.substr(l , temp.size() - l);
        else sub2 = temp.substr(l , r - l);
        if(number.find(sub2) == number.end())
        {
            stop[i].first = sub2;
            number.insert(make_pair(sub2 , i));
            pos2 = i;
            i ++;
        }
        else pos2 = number.find(sub2)->second;
        stop[pos1].second.emplace_back(name , sub2);
        stop[pos2].second.emplace_back(name , sub1);
        pos1 = pos2;
        while(r != std::__cxx11::string::npos)
        {
            l = r + 1;
            r = temp.find(',' , r + 1);
            sub1 = sub2;
            if(r == std::__cxx11::string::npos)sub2 = temp.substr(l , temp.size() - l);
            else sub2 = temp.substr(l , r - l);
            if(number.find(sub2) == number.end())
            {
                stop[i].first = sub2;
                number.insert(make_pair(sub2 , i));
                pos2 = i;
                i ++;
            }
            else pos2 = number.find(sub2)->second;
            stop[pos1].second.emplace_back(name , sub2);
            stop[pos2].second.emplace_back(name , sub1);
            pos1 = pos2;
        }
    }
    /*for(const auto &x: stop)
    {
        string name = x.first;
        for(const auto &y: x.second)
        {
            string next = y.first;
            if(bus.find(name) == bus.end())
            {
                set<string> temp;
                temp.insert(next);
                bus.insert(make_pair(name , temp));
            }
            else bus.find(name)->second.insert(next);
        }
    }*/
    /*for(const auto &x: bus)
    {
        cout << x.first << ": ";
        for(const auto &y: x.second)
        {
            cout << y << ' ';
        }
        cout << endl;
    }*/
    int visit[10010] = {};
    cout << "�����������յ�վ:" << endl;
    string z = "վ";
    string start , end;
    start = "�Ϻ�����";
    end = "�Ͼ���վ";
    //cin >> start >> end;
    start += z;
    end += z;
    int temp = 0;
    while(number.find(start) == number.end() || number.find(end) == number.end())
    {
        cout << "վ̨������������������! " << endl;
        cin >> start >> end;
    }
    temp = number.find(start)->second;
    visit[temp] = 1;
    string l;
    queue<pair<string , string>> q;
    q.push(make_pair(l , start));
    unordered_map<string , pair<string , string>> ret;
    bfs(stop , number , q , end , visit  , ret);
}