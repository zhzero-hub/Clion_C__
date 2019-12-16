// INFO BEGIN
//
// User = 201911508559(Ö£ºÃ) 
// Group = C/C++ 
// Problem = Çø¿éÁ´ 
// Language = CPP11 
// SubmitTime = 2019-12-15 16:24:45 
//
// INFO END

#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

struct Node
{
    int data = 0;
    list<int> link;
    vector<Node *> adj;
    vector<list<int>> wait[2010];
};

int getNum(string &line , int a[])
{
	int size = line.size();
	int ret = 0;
	for(int i = 0;i < size;i ++)
	{
		int num = 0;
		while(line[i] >= '0' && line[i] <= '9')
		{
			num *= 10;
			num += line[i] - '0';
			i ++;
		}
		a[ret ++] = num;
	}
	return ret;
}

void Swap(list<int> &a , list<int> &b)
{
	a.clear();
	for(const auto &x: b)a.insert(a.end() , x);
}

void Do(vector<Node> &a , int &time , int &t)
{
	for(auto &x: a)
	{
		if(x.wait[time].empty())continue;
		for(auto &y: x.wait[time])
		{
			bool status = false;
			if(x.link.size() > y.size())
			{
				continue;
			}
			else if(x.link.size() == y.size())
			{
				if(y.front() < x.link.front())
				{
					Swap(x.link , y);
					status = true;
				}
			}
			else
			{
				Swap(x.link , y);
				status = true;
			}
			if(status)
			{
				for(const auto &y: x.adj)
				{
					a[y->data].wait[time + t].push_back(x.link);
				}
			}
		}
	}
	time ++;
}

int main()
{
    int m , n;
    cin >> n >> m;
    vector<Node> a;
    for(int i = 0;i <= n;i ++)
    {
        Node temp;
        temp.data = i;
        temp.link.push_back(0);
        a.push_back(temp);
    }
    for(int i = 1;i <= m;i ++)
    {
        int l , r;
        cin >> l >> r;
        a[l].adj.push_back(&a[r]);
        a[r].adj.push_back(&a[l]);
    }
	int t , k;
	int time = 0;
	cin >> t >> k;
	getchar();
	for(;k > 0;k --)
	{
		int q[3] = {};
		string temp;
		getline(cin , temp);
		getNum(temp , q);
		while(time <= q[1])
		{
			Do(a , time , t);
		}
		if(getNum(temp , q) == 3)
		{
			a[q[0]].link.insert(a[q[0]].link.begin() , q[2]);
			for(const auto &y: a[q[0]].adj)
			{
				a[y->data].wait[time + t - 1].push_back(a[q[0]].link);
			}
		}
		else
		{
			cout << a[q[0]].link.size();
			for(auto it = --a[q[0]].link.end();it != a[q[0]].link.begin();it --)cout << ' ' << *it;
			cout << ' ' << a[q[0]].link.front() << endl;
		}
	}
}