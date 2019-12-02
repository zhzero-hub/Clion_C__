//
// Created by Z_HAO on 2019/11/28.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int Find(const vector<pair<string , string>> &x , const string& t , int pos = 0)//从pos开始找t
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

void dfs(vector<pair<string , vector<pair<string , string>>>> &stop , unordered_map<string , int> &number , string &x , string& name , string &end , int *visit , vector<pair<string , string>> &path)
{
    if(x == end) {
        for (const auto &y: path)cout << "(" << y.first << ")" << y.second << ' ';
        cout << endl;
        cout << path.size() << endl;
        return;
    }
    if(path.size() > 30)
        return;
    int pos = number.find(x)->second;
    int p = Find(stop[pos].second , name);
        while(p != stop[pos].second.size())
        {
            string temp = stop[pos].second[p].second;//同一路的下一站
            if(!visit[number.find(temp)->second])
            {
                visit[number.find(temp)->second] = 1;
                path.emplace_back(make_pair(name , temp));
                dfs(stop , number , stop[pos].second[p].second , name , end , visit , path);
                visit[number.find(temp)->second] = 0;
                path.pop_back();
            }
            p = Find(stop[pos].second , name , p + 1);
        }
    for(const auto &y: stop[pos].second) {
        string temp = y.second;
        if (!visit[number.find(temp)->second]) {
            visit[number.find(temp)->second] = 1;
            path.emplace_back(y.first, temp);
            name = y.first;
            x = temp;
            dfs(stop , number , x , name , end , visit , path);
            visit[number.find(temp)->second] = 0;
            path.pop_back();
        }
    }
}

int main()
{
    unordered_map<string , int> number;
    vector<pair<string , vector<pair<string , string>>>> stop(5130);//5127????
    ifstream file("Bus.txt");
    if(file.fail())
    {
        cout << "文件不存在! "<< endl;
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
    int visit[10010] = {};
    vector<pair<string , string>> path;
    cout << "请输入起点和终点站:" << endl;
    string z = "站";
    string start , end;
    start = "南航北门";
    end = "南航江宁校区北门";
    //cin >> start >> end;
    start += z;
    end += z;
    int temp = 0;
    while(number.find(start) == number.end() || number.find(end) == number.end())
    {
        cout << "站台输入有误，请重新输入! " << endl;
        cin >> start >> end;
    }
    temp = number.find(start)->second;
    visit[temp] = 1;
    string l;
    path.emplace_back(l , start);
    dfs(stop , number , start , l , end , visit , path);
}