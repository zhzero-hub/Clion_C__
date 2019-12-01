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

void dfs(vector<pair<string , vector<pair<string , string>>>> &stop , unordered_map<string , int> &number , string &x , const string& name , string &end , int *visit , vector<pair<string , string>> &path)
{
    if(x == end) {
        for (const auto &y: path)cout << "(" << y.first << ")" << y.second << ' ';
        cout << endl;
    }
    int pos = number.find(x)->second;
    int p = Find(stop[pos].second , name);
    if(p != stop[pos].second.size())
    {
        while(p != stop[pos].second.size())
        {
            string temp = stop[pos].second[p].second;
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
    }
    else
    {
        for(const auto &y: stop[pos].second)
        {
            string temp = y.second;
            if(!visit[number.find(temp)->second])
            {
                visit[number.find(temp)->second] = 1;
                path.emplace_back(y.first , temp);
                dfs(stop , number , temp , y.first , end , visit , path);
                visit[number.find(temp)->second] = 0;
                path.pop_back();
            }
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
        string sub2 = temp.substr(l , r - l);
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
            if(r == std::__cxx11::string::npos)break;
            sub1 = sub2;
            sub2 = temp.substr(l , r - l);
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
    cin >> start;
    cout << start << endl;
    int temp = 0;
    if(number.find(start) == number.end())
    {
        cout << "2333" << endl;
    }
    else temp = number.find(start)->second;
    visit[temp] = 1;
    string l;
    path.emplace_back(l , start);
    dfs(stop , number , start , l , end , visit , path);
}