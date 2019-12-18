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

vector<pair<string , vector<pair<string , string>>>> stop(5130);//5126��վ
// x.first��ʾվ����x.second.second��ʾ��һվ��վ��s.second.first��ʾ�����վȥ��һվ�Ĺ�����
unordered_map<string , int> number;//�洢stringվ��stop�����е�λ��
vector<pair<string , unordered_set<string>>> bus(991);
//x.first��ʾĳһ·����������������bus�����е�λ��һ�£���x.second�������ܺ�x.first���ൽ����ˣ��Ĺ�������·�ļ���

int Find(const vector<pair<string , string>> &x , const string& t , int pos = 0)//��pos��ʼ��t��O(n)
{//stop.second����ĳһ�ض���·�Ĺ�����
    int size = x.size();
    for(int i = pos;i < size;i ++)if(x[i].first == t)return i;
    return size;//�Ҳ�������βԪ�غ�һ��Ԫ�ص�λ��
}

int to_int(const string &x)//��Ϊ������·�����һ��վ��������ʱ����Ҫ��ȡ��·�����֣�O(n)
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

bool Create_graph()//����ͼ���ɹ�����true
{
    ifstream file("Bus.txt");
    if(file.fail())
    {
        cout << "�ļ�������! "<< endl;
        return false;
    }
    int i = 0;//i��Ӧstop�����һ��Ԫ�صĺ�һ��Ԫ�ص�λ�ã������½�վ
    while(!file.eof())
    {
        string name;
        file >> name;//name��ʾ������·��
        int t = to_int(name);
        bus[t].first = name;//bus���½�name
        int pos1 = -1 , pos2 = -1;
        string temp;
        file >> temp;//temp�Ǻ���һ�󴮹���վ���ַ������������"��"����ÿһ��վ
        int l = 0;//[l , r - 1]����һ��վ��
        int r = temp.find(',');
        string sub1 = temp.substr(l , r - l);
        if(number.find(sub1) == number.end())//������վ��stop��֮ǰû�г��ֹ�
        {
            stop[i].first = sub1;
            number.insert(make_pair(sub1 , i));//stop���½�һ��վ
            pos1 = i;//���վ��stop�е�λ�þ����½���λ��
            i ++;
        }
        else pos1 = number.find(sub1)->second;//�������stop��֮ǰ���ֹ���λ�ã�O(1)��ѯ
        l = r + 1;
        r = temp.find(',' , r + 1);//��ȡ��һ��վ
        string sub2;
        if(r == std::__cxx11::string::npos)sub2 = temp.substr(l , temp.size() - l);//��Ϊ�п������������·ֻ������վ���Ҳ�����һ��","����ʱ���һ��վ����
        else sub2 = temp.substr(l , r - l);
        if(number.find(sub2) == number.end())//ͬ�ϴ���
        {
            stop[i].first = sub2;
            number.insert(make_pair(sub2 , i));
            pos2 = i;
            i ++;
        }
        else pos2 = number.find(sub2)->second;
        stop[pos1].second.emplace_back(name , sub2);
        stop[pos2].second.emplace_back(name , sub1);//��stop��������վ�������Է�
        pos1 = pos2;//sub2���sub1
        while(r != std::__cxx11::string::npos)//�ظ���Ӳ���
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
    for(auto &x: stop)//����stop����bus
    {//stop��ÿ��һ��վ�в�ͬ�Ĺ�����·����˵�����ǿ��Ի��ൽ�O(n^2)
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
{   //Ѱ��start��end�Ľ�����·
    //��start��end�ܵ���Ĺ�����·��
    int p = number.find(start)->second;
    int q = number.find(end)->second;
    set<string> a , b , c;
    unordered_map<string , string> map;//map��<x, y>��ʾx��ͨ��y��ӽ����ģ����ڻ���
    int visit[10010] = {};//visit�洢�Ѿ����ʹ���վ
    for(const auto &x: stop[p].second)//�����ܵ�start��վ����a������
    {
        visit[to_int(x.first)] = 1;
        a.insert(x.first);
    }
    for(const auto &x: stop[q].second)//�����ܵ�end��վ����b������
    {
        b.insert(x.first);
    }
    while(true)
    {
        //�������ϵĽ���
        set_intersection(a.begin() , a.end() , b.begin() , b.end() , insert_iterator<set<string>>(c , c.begin()));
        if(!c.empty())//��Ϊ�գ���ʾ����Ԫ�ؾ��ǿ��Ի��ൽ��ĳ�
        {
            for(auto &x: c)//���н���Ԫ�طŽ�������
            {
                vector<string> temp;
                string t = x;
                while(map.find(t) != map.end())//���ݣ�x�ǻ��ൽ��ĳ���x��y��ӽ����ģ�Ӧ���ȳ�y�ٳ�x�����Դ�����
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
            for(const auto &x: a)//�ҵ����к�a��ͨ�ĳ�
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
            //��a����
            set_union(a.begin() , a.end() , t.begin() , t.end() , insert_iterator<set<string>>(swap , swap.end()));
            t.clear();
            swap.swap(a);
            swap.clear();
        }
    }
    cout << "���ٻ��˳���Ϊ: " << endl;
    for(const auto &x: ans)
    {
        for(const auto &y: x)cout << y << ' ';
        cout << endl;
    }
}

bool Intersection_path(vector<vector<string>> &ans , string &start , string &end)//�������ٻ��˷�ʽ�ҵ�����·��
{
    vector<vector<pair<string , string>>> path;//ÿһ��path��Ӧһ��·��
    for(const auto &y: ans)//�������з���
    {
        int visit[10010] = {};//visit����洢�Ѿ����ʹ���վ
        visit[number.find(start)->second] = 1;//���վ��Ϊ����״̬
        unordered_map<string , pair<string , string>> map;//map���ڻ��ݣ�<x, y>��ʾy.secondͨ��y.first���Ե���x
        int size = y.size();//size - 1��ʾ���˴���
        queue<pair<string , string>> que;//que����bfs
        que.push(make_pair(y[0] , start));
        int i = 1;//y[i - 1]�ǵ�ǰ·�ߣ�y[i]����һ�����˵�·��
        while(!que.empty())
        {
            auto x = que.front();
            que.pop();
            if(x.second == end)//�����յ�
            {
                vector<pair<string , string>> temp;
                temp.push_back(x);
                string t = x.second;
                while(map.find(t) != map.end())//���·��
                {
                    auto z = map.find(t)->second;
                    temp.insert(temp.begin() , z);
                    t = z.second;
                }
                path.push_back(temp);
                break;
            }
            int pos = number.find(x.second)->second;//stop[pos]Ϊ��ǰվ
            int p = Find(stop[pos].second , y[i - 1]);//p��ʾ��ǰ·����stop[pos].second����һվ��λ��
            int q = stop[pos].second.size();//q��ʾ��һ��ת��·�ߵ�λ��
            if(i < size)q = Find(stop[pos].second , y[i]);//���ת��·���к����Ѿ�����Ҫת��������Ҫ�ı�q
            if(q != stop[pos].second.size())//����ת����ת��
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
            else//�����Ծ�ȥ��һվ
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
    cout << "���˷�ʽΪ: " << endl;//���·��
    for(const auto &x: path)
    {
        int size = x.size();
        cout << x[0].second;
        for(int i = 1;i < size;i ++)
        {
            cout << "--->" << "(" << x[i].first << ")" << x[i].second;
        }
        cout << endl;
        cout << "��" << x.size() - 1 << "վ" << endl;
    }
    return true;
}

bool bfs(string &start , string &end)
{
    int visit[10010] = {};//visit����洢�Ѿ����ʹ���վ
    visit[number.find(start)->second] = 1;//startվ��Ϊ����״̬
    string l;
    queue<pair<string , string>> q;//q������bfs�Ķ���
    q.push(make_pair(l , start));
    unordered_map<string , pair<string , string>> ret;//ret���ڻ��ݣ�<x, y>��ʾx���Դ�y.secondͨ��y.first����
    while(!q.empty())
    {
        auto x = q.front();
        q.pop();
        int flag = 0;
        if(x.second == end) {//�ҵ��յ�
            string t = x.second;
            vector<pair<string, string>> path;
            while (ret.find(t) != ret.end()) {//����·����������뵽path��
                auto y = ret.find(t)->second;
                path.insert(path.begin(), y);
                t = y.second;
            }
            cout << "����վ���ٵ�·��Ϊ: " << endl;
            for (const auto &y: path) {//���path
                if (y.first.empty())cout << y.second << "-->";
                else cout << "(" << y.first << ")" << y.second << "-->";
            }
            cout << "(" << x.first << ")" << end << endl;
            cout << "��" << path.size() << "վ" << endl;
            return true;//Ѱ�ҳɹ�
        }
        if(number.find(x.second) == number.end())return false;//stop��û��x.secondվ
        int pos = number.find(x.second)->second;
        int p = Find(stop[pos].second , x.first);//�Ƚ�ͬһ·��վ�������
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
        for(const auto &y: stop[pos].second) {//�ٽ���ͬ·�ļ������
            string t = y.second;
            if (!visit[number.find(t)->second]) {
                visit[number.find(t)->second] = 1;
                q.push(y);
                ret.insert(make_pair(y.second , x));
                flag ++;
            }
        }
    }
    return false;//û���ҵ��յ㣬Ѱ��ʧ��
}

int main()
{
    if(Create_graph()) {
        cout << "·�ߴ����ɹ�" << endl;
    }
    else {
        cout << "����ʧ��" << endl;
        return 0;
    }
    cout << "�����������յ�վ:" << endl;
    string z = "վ";
    string start , end;
    cin >> start >> end;//�������������
    //start = "�Ϻ�����";
    //end = "�Ϻ�����У������";
    start += z;
    end += z;
    while(number.find(start) == number.end() || number.find(end) == number.end())//stop���Ҳ���start��endվ
    {
        cout << "վ̨������������������! " << endl;
        cin >> start >> end;
    }
    if(!bfs(start , end)){
        cout << "Error! " << endl;
    };
    vector<vector<string>> ch;
    Find_intersection(start , end , ch);
    Intersection_path(ch , start , end);
}