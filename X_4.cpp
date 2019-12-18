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
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<pair<string , vector<pair<string , string>>>> stop(5130);//5126个站
// x.first表示站名，x.second.second表示下一站的站名s.second.first表示从这个站去下一站的公交车
unordered_map<string , int> number;//存储string站在stop数组中的位置
vector<pair<string , unordered_set<string>>> bus(991);
//x.first表示某一路公交车（与它所在bus数组中的位置一致），x.second是所有能和x.first互相到达（换乘）的公交车线路的集合

int Find(const vector<pair<string , string>> &x , const string& t , int pos = 0)//从pos开始找t，O(n)
{//stop.second中找某一特定线路的公交车
    int size = x.size();
    for(int i = pos;i < size;i ++)if(x[i].first == t)return i;
    return size;//找不到返回尾元素后一个元素的位置
}

int to_int(const string &x)//因为公交线路最后有一个站，所以有时候需要提取线路的数字，O(n)
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

bool Create_graph()//创建图，成功返回true
{
    ifstream file("Bus.txt");
    if(file.fail())
    {
        cout << "文件不存在! "<< endl;
        return false;
    }
    int i = 0;//i对应stop中最后一个元素的后一个元素的位置，用于新建站
    while(!file.eof())
    {
        string name;
        file >> name;//name表示公交线路名
        int t = to_int(name);
        bus[t].first = name;//bus中新建name
        int pos1 = -1 , pos2 = -1;
        string temp;
        file >> temp;//temp是后面一大串公交站的字符串，后面根据"，"区分每一个站
        int l = 0;//[l , r - 1]就是一个站名
        int r = temp.find(',');
        string sub1 = temp.substr(l , r - l);
        if(number.find(sub1) == number.end())//如果这个站在stop中之前没有出现过
        {
            stop[i].first = sub1;
            number.insert(make_pair(sub1 , i));//stop中新建一个站
            pos1 = i;//这个站在stop中的位置就在新建的位置
            i ++;
        }
        else pos1 = number.find(sub1)->second;//否则就在stop中之前出现过的位置，O(1)查询
        l = r + 1;
        r = temp.find(',' , r + 1);//提取下一个站
        string sub2;
        if(r == std::__cxx11::string::npos)sub2 = temp.substr(l , temp.size() - l);//因为有可能这个公交线路只有两个站，找不到下一个","，此时最后一个站就是
        else sub2 = temp.substr(l , r - l);
        if(number.find(sub2) == number.end())//同上创建
        {
            stop[i].first = sub2;
            number.insert(make_pair(sub2 , i));
            pos2 = i;
            i ++;
        }
        else pos2 = number.find(sub2)->second;
        stop[pos1].second.emplace_back(name , sub2);
        stop[pos2].second.emplace_back(name , sub1);//在stop中这两个站互相加入对方
        pos1 = pos2;//sub2变成sub1
        while(r != std::__cxx11::string::npos)//重复添加操作
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
    for(auto &x: stop)//根据stop创建bus
    {//stop中每有一个站有不同的公交线路，就说明它们可以互相到达，O(n^2)
        int size = x.second.size();
        for(int k = 0;k < size;k ++)
        {
            for(int j = k + 1;j < size;j ++)
            {
                int p = to_int(x.second[k].first);
                int q = to_int(x.second[j].first);
                bus[p].second.insert(x.second[j].first);
                bus[q].second.insert(x.second[k].first);
            }
        }
    }
    return true;
}

void Find_intersection(const string &start , const string &end , vector<vector<string>> &ans)
{   //寻找start和end的交集线路
    //将start和end能到达的公交线路中
    int p = number.find(start)->second;
    int q = number.find(end)->second;
    set<string> a , b , c;
    unordered_map<string , string> map;//map中<x, y>表示x是通过y添加进来的，用于回溯
    int visit[10010] = {};//visit存储已经访问过的站
    for(const auto &x: stop[p].second)//所有能到start的站放在a集合中
    {
        visit[to_int(x.first)] = 1;
        a.insert(x.first);
    }
    for(const auto &x: stop[q].second)//所有能到end的站放在b集合中
    {
        b.insert(x.first);
    }
    while(true)
    {
        //求两集合的交集
        set_intersection(a.begin() , a.end() , b.begin() , b.end() , insert_iterator<set<string>>(c , c.begin()));
        if(!c.empty())//不为空，表示交集元素就是可以互相到达的车
        {
            for(auto &x: c)//所有交集元素放进数组中
            {
                vector<string> temp;
                string t = x;
                while(map.find(t) != map.end())//回溯，x是互相到达的车，x是y添加进来的，应该先乘y再乘x……以此类推
                {
                    temp.insert(temp.begin() , t);
                    t = map.find(t)->second;
                }
                temp.insert(temp.begin() , t);
                ans.push_back(temp);
            }
            break;
        }
        else
        {
            set<string> t;
            for(const auto &x: a)//找到所有和a互通的车
            {
                int temp = to_int(x);
                for(const auto &y: bus[temp].second)
                {
                    if(!visit[to_int(y)])
                    {
                        t.insert(y);
                        visit[to_int(y)] = 1;
                        map.insert(make_pair(y , x));
                    }
                }
            }
            set<string> swap;
            //将a扩大
            set_union(a.begin() , a.end() , t.begin() , t.end() , insert_iterator<set<string>>(swap , swap.end()));
            t.clear();
            swap.swap(a);
            swap.clear();
        }
    }
    cout << "最少换乘车辆为: " << endl;
    for(const auto &x: ans)
    {
        for(const auto &y: x)cout << y << ' ';
        cout << endl;
    }
}

bool Intersection_path(vector<vector<string>> &ans , string &start , string &end)//根据最少换乘方式找到公交路线
{
    vector<vector<pair<string , string>>> path;//每一个path对应一条路线
    for(const auto &y: ans)//遍历所有方案
    {
        int visit[10010] = {};//visit数组存储已经访问过的站
        visit[number.find(start)->second] = 1;//起点站设为访问状态
        unordered_map<string , pair<string , string>> map;//map用于回溯，<x, y>表示y.second通过y.first可以到达x
        int size = y.size();//size - 1表示换乘次数
        queue<pair<string , string>> que;//que用于bfs
        que.push(make_pair(y[0] , start));
        int i = 1;//y[i - 1]是当前路线，y[i]是下一个换乘的路线
        while(!que.empty())
        {
            auto x = que.front();
            que.pop();
            if(x.second == end)//到达终点
            {
                vector<pair<string , string>> temp;
                temp.push_back(x);
                string t = x.second;
                while(map.find(t) != map.end())//输出路径
                {
                    auto z = map.find(t)->second;
                    temp.insert(temp.begin() , z);
                    t = z.second;
                }
                path.push_back(temp);
                break;
            }
            int pos = number.find(x.second)->second;//stop[pos]为当前站
            int p = Find(stop[pos].second , y[i - 1]);//p表示当前路线在stop[pos].second中下一站的位置
            int q = stop[pos].second.size();//q表示下一个转车路线的位置
            if(i < size)q = Find(stop[pos].second , y[i]);//如果转车路线中后面已经不需要转车，则不需要改变q
            if(q != stop[pos].second.size())//可以转车就转车
            {
                while(q != stop[pos].second.size())
                {
                    string temp = stop[pos].second[q].second;
                    if(!visit[number.find(temp)->second])
                    {
                        que.push(stop[pos].second[q]);
                        map.insert(make_pair(temp , x));
                        visit[number.find(temp)->second] = 1;
                    }
                    q = Find(stop[pos].second , y[i] , q + 1);
                }
                i ++;
                if(i > size)return false;
            }
            else//不可以就去下一站
            {
                while(p != stop[pos].second.size())
                {
                    string temp = stop[pos].second[p].second;
                    if(!visit[number.find(temp)->second])
                    {
                        que.push(stop[pos].second[p]);
                        map.insert(make_pair(temp , x));
                        visit[number.find(temp)->second] = 1;
                    }
                    p = Find(stop[pos].second , y[i - 1] , p + 1);
                }
            }
        }
    }
    cout << "换乘方式为: " << endl;//输出路线
    for(const auto &x: path)
    {
        int size = x.size();
        cout << x[0].second;
        for(int i = 1;i < size;i ++)
        {
            cout << "--->" << "(" << x[i].first << ")" << x[i].second;
        }
        cout << endl;
        cout << "共" << x.size() - 1 << "站" << endl;
    }
    return true;
}

bool bfs(string &start , string &end)
{
    int visit[10010] = {};//visit数组存储已经访问过的站
    visit[number.find(start)->second] = 1;//start站设为访问状态
    string l;
    queue<pair<string , string>> q;//q是用于bfs的队列
    q.push(make_pair(l , start));
    unordered_map<string , pair<string , string>> ret;//ret用于回溯，<x, y>表示x可以从y.second通过y.first到达
    while(!q.empty())
    {
        auto x = q.front();
        q.pop();
        int flag = 0;
        if(x.second == end) {//找到终点
            string t = x.second;
            vector<pair<string, string>> path;
            while (ret.find(t) != ret.end()) {//回溯路径，将其加入到path中
                auto y = ret.find(t)->second;
                path.insert(path.begin(), y);
                t = y.second;
            }
            cout << "经过站最少的路线为: " << endl;
            for (const auto &y: path) {//输出path
                if (y.first.empty())cout << y.second << "-->";
                else cout << "(" << y.first << ")" << y.second << "-->";
            }
            cout << "(" << x.first << ")" << end << endl;
            cout << "共" << path.size() << "站" << endl;
            return true;//寻找成功
        }
        if(number.find(x.second) == number.end())return false;//stop中没有x.second站
        int pos = number.find(x.second)->second;
        int p = Find(stop[pos].second , x.first);//先将同一路的站加入队列
        while(p != stop[pos].second.size())
        {
            string t = stop[pos].second[p].second;
            if(!visit[number.find(t)->second])
            {
                visit[number.find(t)->second] = 1;
                q.push(stop[pos].second[p]);
                ret.insert(make_pair(t , x));
                flag ++;
            }
            p = Find(stop[pos].second , x.first , p + 1);
        }
        for(const auto &y: stop[pos].second) {//再将不同路的加入队列
            string t = y.second;
            if (!visit[number.find(t)->second]) {
                visit[number.find(t)->second] = 1;
                q.push(y);
                ret.insert(make_pair(y.second , x));
                flag ++;
            }
        }
    }
    return false;//没能找到终点，寻找失败
}

int main()
{
    if(Create_graph()) {
        cout << "路线创建成功" << endl;
    }
    else {
        cout << "创建失败" << endl;
        return 0;
    }
    cout << "请输入起点和终点站:" << endl;
    string z = "站";
    string start , end;
    cin >> start >> end;//输入编码有问题
    //start = "南航北门";
    //end = "南航江宁校区北门";
    start += z;
    end += z;
    while(number.find(start) == number.end() || number.find(end) == number.end())//stop中找不到start或end站
    {
        cout << "站台输入有误，请重新输入! " << endl;
        cin >> start >> end;
    }
    if(!bfs(start , end)){
        cout << "Error! " << endl;
    };
    vector<vector<string>> ch;
    Find_intersection(start , end , ch);
    Intersection_path(ch , start , end);
}