//
// Created by Z_HAO on 2019/12/27.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <graphics.h>
#include <conio.h>
#include <iterator>

using namespace std;
int M;

struct Node
{
	vector<pair<Node *, int>> data;
	Node *end = nullptr;
};

unsigned long long int ceil(unsigned long long int x)//[x/2]向上取整
{
	return (x - 1) / 2 + 1;
}

unsigned long long int Binary_search(const vector<pair<Node *, int>> &x, const int &t, unsigned long long int l, unsigned long long int r)//O(log(x.size()))
{//二分查找，只确定范围。对于一个数t，返回它在数组中所有小于等于它的下标中最大的那一个，如果是大于所有元素，返回最后一个元素的下标
	if (l == r)
	{
		return l;
	}
	unsigned long long int mid = (l + r) / 2;
	unsigned int ret = 0;
	if (t < x[mid].second)
	{
		ret = Binary_search(x, t, l, mid);
	}
	else if (t > x[mid].second)
	{
		ret = Binary_search(x, t, mid + 1, r);
	}
	else if (t == x[mid].second)
	{
		return mid;
	}
	return ret;
}

void Show(Node *x, int layer = 0)
{
	if (x == nullptr)return;
	cout << layer << "层: ";
	for (const auto &y : x->data)
	{
		cout << y.second << ' ';
	}
	cout << endl;
	for (const auto &y : x->data)
	{
		Show(y.first, layer + 1);
	}
	Show(x->end, layer + 1);
}

Node *Insert(Node *x, const int &t, pair<Node *, int> &up, int layer)
{
	if (x == nullptr)
	{
		Node *base = new Node;
		base->end = nullptr;
		base->data.emplace_back(nullptr, t);
		return base;
	}
	unsigned long long int pos = Binary_search(x->data, t, 0, x->data.size() - 1);//二分查找
	if (x->data[pos].second == t)//树中已经有这个值，直接返回
	{
		return x;
	}
	if (x->end == nullptr)//最后一层
	{
		if (t > x->data[pos].second)pos++;//如果大于所有树中的元素，则插入到最后
		x->data.insert(x->data.begin() + pos, make_pair(nullptr, t));
	}
	else {
		if (t < x->data[pos].second)
		{
			x->data[pos].first = Insert(x->data[pos].first, t, up, layer + 1);//递归插入
		}
		else if (t > x->data[pos].second)
		{
			x->end = Insert(x->end, t, up, layer + 1);
		}
	}
	if (up.first != nullptr)//查看是否有要顶上来的元素
	{
		if (up.second > x->data[pos].second)pos++;
		x->data.insert(x->data.begin() + pos, up);
		up.first = nullptr;
	}
	if (x->data.size() == M)//往上顶
	{
		int mid = M / 2;
		if (layer == 0)//根节点分裂
		{
			Node *base = new Node;
			Node *l = new Node;
			Node *r = new Node;
			base->end = l->end = r->end = nullptr;
			base->data.emplace_back(l, x->data[mid].second);
			base->end = r;
			copy(x->data.begin(), x->data.begin() + mid, insert_iterator<vector<pair<Node *, int>>>(l->data, l->data.end()));
			l->end = x->data[mid].first;
			copy(x->data.begin() + mid + 1, x->data.end(), insert_iterator<vector<pair<Node *, int>>>(r->data, r->data.end()));
			r->end = x->end;
			delete x;
			up.first = nullptr;
			return base;
		}
		Node *node = new Node;
		copy(x->data.begin(), x->data.begin() + mid, insert_iterator<vector<pair<Node *, int>>>(node->data, node->data.end()));
		auto it = x->data.erase(x->data.begin(), x->data.begin() + mid);
		up.first = node;
		node->end = it->first;
		up.second = it->second;
		x->data.erase(x->data.begin());
	}
	return x;
}

bool Find(Node *x, const int &t)
{
	unsigned long long int pos = Binary_search(x->data, t, 0, x->data.size() - 1);
	if (x->data[pos].second == t)
	{
		return true;
	}
	if (x->end == nullptr)
	{
		return false;
	}
	else
	{
		if (t > x->data[pos].second)
		{
			return Find(x->end, t);
		}
		return Find(x->data[pos].first, t);
	}
}

Node *Delete(Node *x, const int &t, int &flag)
{
	unsigned long long int pos = Binary_search(x->data, t, 0, x->data.size() - 1);
	if (x->data[pos].second == t)
	{
		if (x->end == nullptr)//删除的是叶节点
		{
			x->data.erase(x->data.begin() + pos);
		}
		else {//非叶节点
			// 若该结点为非叶结点，且被删关键字为该结点中第i个关键字key[i]，则可从指针son[i]所指的子树中找出最小关键字Y，代替key[i]的位置，然后在叶结点中删去Y
			if (pos < x->data.size() - 1)
			{
				int del = x->data[pos + 1].first->data.front().second;
				x->data[pos].second = del;//如果不存在怎么办?
				x->data[pos + 1].first = Delete(x->data[pos + 1].first, del, flag);
			}
			else {
				int del = x->end->data.front().second;
				x->data[pos].second = del;//如果不存在怎么办?
				x->end = Delete(x->end, del, flag);
			}
		}
	}
	else if (x->end == nullptr)
	{
		cout << "未找到该节点" << endl;
	}
	else {
		if (t > x->data[pos].second)
		{
			x->end = Delete(x->end, t, flag);
		}
		else {
			x->data[pos].first = Delete(x->data[pos].first, t, flag);
		}
	}
	int size = x->data.size();
	if (flag)
	{
		if (pos == 0)
		{
			if (size == 1)//只可能出现在M=3的时候
			{
				if (!x->end && x->end->data.size() >= ceil(M))
				{
					x->data[0].first->data.emplace_back(nullptr, x->data[0].second);
					x->data[0].second = x->end->data[0].second;
					x->end->data.erase(x->end->data.begin());
					flag = 0;
					return x;
				}
			}
			else {//0号位只有右兄弟
				if (!x->data[pos + 1].first && x->data[pos + 1].first->data.size() >= ceil(M))
				{
					x->data[pos + 1].first->data.emplace_back(nullptr, x->data[pos + 1].second);
					x->data[pos + 1].second = x->data[pos + 1].first->data[0].second;
					x->data[pos + 1].first->data.erase(x->data[pos + 1].first->data.begin());
					flag = 0;
					return x;
				}
			}
		}
		else if (pos == size - 1)//只有左兄弟
		{
			if (t > x->data[pos].second)//end删除
			{
				if (!x->data[pos].first && x->data[pos].first->data.size() >= ceil(M))//查看倒数第二个是否可以顶上去
				{//可以的话是最后一个顶上去
					x->end->data.emplace_back(nullptr, x->data[pos].second);
					x->data[pos].second = x->data[pos].first->data[x->data[pos].first->data.size() - 1].second;
					x->data[pos].first->data.pop_back();
					flag = 0;
					return x;
				}
			}
			else {//倒数第二个删除，右兄弟在end上
				if (!x->data[pos - 1].first && x->data[pos - 1].first->data.size() >= ceil(M))
				{
					x->data[pos - 1].first->data.emplace_back(nullptr, x->data[pos - 1].second);
					x->data[pos - 1].second = x->data[pos - 1].first->data[x->data[pos - 1].first->data.size() - 1].second;
					x->data[pos - 1].first->data.pop_back();
					flag = 0;
					return x;
				}
				else if (!x->end && x->end->data.size() >= ceil(M))//在右兄弟end上找
				{
					x->data[pos].first->data.emplace_back(nullptr, x->data[pos].second);
					x->data[pos].second = x->end->data[0].second;
					x->end->data.erase(x->end->data.begin());
					flag = 0;
					return x;
				}
			}
		}
		else {//左右都有兄弟
			if (!x->data[pos + 1].first && x->data[pos + 1].first->data.size() >= ceil(M))
			{
				x->data[pos + 1].first->data.emplace_back(nullptr, x->data[pos + 1].second);
				x->data[pos + 1].second = x->data[pos + 1].first->data[0].second;
				x->data[pos + 1].first->data.erase(x->data[pos + 1].first->data.begin());
				flag = 0;
				return x;
			}
			else if (!x->data[pos - 1].first && x->data[pos - 1].first->data.size() >= ceil(M))
			{
				x->data[pos - 1].first->data.emplace_back(nullptr, x->data[pos - 1].second);
				x->data[pos - 1].second = x->data[pos - 1].first->data[x->data[pos - 1].first->data.size() - 1].second;
				x->data[pos - 1].first->data.pop_back();
				flag = 0;
				return x;
			}
		}
	}
	if (flag)//左右兄弟没有可以换的节点，上面的拉下去合并
	{
		if (pos == size - 1)//pos-1和end合并
		{
			x->data[pos].first->data.emplace_back(x->data[pos].first->end, x->data[pos].second);
			copy(x->end->data.begin(), x->end->data.end(), insert_iterator<vector<pair<Node *, int>>>(x->data[pos].first->data, x->data[pos].first->data.end()));
			x->data[pos].first->end = x->end->end;
			delete x->end;
			x->end = x->data[pos].first;
			x->data.erase(x->data.begin() + pos);
			if (x->data.empty())//这里不剩元素了
			{
				Node *ret = x->data[pos].first;
				flag = 0;
				delete x;
				return ret;
			}
		}
		else {//pos和pos+1合并
			x->data[pos].first->data.emplace_back(x->data[pos].first->end, x->data[pos].second);
			copy(x->data[pos + 1].first->data.begin(), x->data[pos + 1].first->data.end(), insert_iterator<vector<pair<Node *, int>>>(x->data[pos].first->data, x->data[pos].first->data.end()));
			x->data[pos].first->end = x->data[pos + 1].first->end;
			delete x->data[pos + 1].first;
			x->data[pos + 1].first = x->data[pos].first;
			x->data.erase(x->data.begin() + pos);
			if (x->data.empty())//这里不剩元素了
			{
				Node *ret = x->data[pos].first;
				flag = 0;
				delete x;
				return ret;
			}
		}
		flag = 0;
		return x;
	}
	//重新判断是否有下溢
	if (x->data.size() < ceil(M) - 1)//下溢
	{
		flag = 1;
	}
	return x;
}

void Draw(Node *base , int nodes[][4], int radius, int k = 1)
{
	if (base != NULL)
	{
		//Draw(T->Left, nodes, radius, 2 * k);
		setlinecolor(BLUE);
		circle(nodes[k][0], nodes[k][1], radius);
		char s[10];
		sprintf_s(s, "%d", nodes[k][3]);
		settextstyle(2 * radius, 0, _T("宋体"));
		outtextxy(nodes[k][0] + radius + 1, nodes[k][1] - radius, s);
		setlinecolor(YELLOW);
		if (nodes[2 * k][2] == 1)
			line(nodes[k][0], nodes[k][1] + radius, nodes[2 * k][0], nodes[2 * k][1] - radius);
		if (nodes[2 * k + 1][2] == 1)
			line(nodes[k][0], nodes[k][1] + radius, nodes[2 * k + 1][0], nodes[2 * k + 1][1] - radius);
		//Draw(T->Right, nodes, radius, 2 * k + 1);
	}
}

void show_node(int left, int top, int right, Node *t)//在指定位置输出一个节点
{
	TCHAR s[5];//用于输出
	int y = top + 20;
	int x = (left + right) / 2 - (3 * t->data.size() + 1) * 7.5;//起始位置
	rectangle(x, y, x + (3 * t->data.size() + 1) * 15, y + 20);
	int i = 0;
	while (i < t->data.size())
	{
		_stprintf_s(s, _T("%d"), t->data[i].second);
		outtextxy(x + 21 + 45 * i, y + 4, s);
		i ++;
	}
}

void show(Node *head, int left, int top, int right)
{
	Node *T = head;
	int flag = 1;
	int step;
	int x;
	int i = 0;
	//以下为输出主干部分
	show_node(left, top, right, T);
	//以下为输出分支部分
	if (T->end != nullptr)
	{
		int size = 1;
		for (const auto &x : T->data)
		{
			if (x.first != nullptr)size++;//size只表示接下来仍有需要输出的节点的个数
		}
		step = (right - left) / size;
		x = (left + right + 1) / 2 - (3 * size + 1) * 7.5;//起始位置
		for (const auto &y: T->data)
		{
			if (y.first != nullptr)
			{
				show(y.first, left + i * step, top + 60, left + (i + 1)*step);//输出当前节点
				line(x + 30 + i * 45, top + 30, left + (2 * i + 1)*step / 2, top + 80);//画线
				i ++;
			}
		}
		show(T->end, left + i * step, top + 60, left + (i + 1)*step);//输出当前节点
		line(x + 30 + i * 45, top + 30, left + (2 * i + 1)*step / 2, top + 80);//画线
	}
}

int main()
{
	Node *base = nullptr;
	pair<Node *, int> up;
	up.first = nullptr;
	int a[10010] = {};
	int n = 0;
	cout << "请输入B-树阶数M: ";
	cin >> M;
	cout << "请输入数据规模n: ";
	cin >> n;
	for (int i = 0; i < n; i++)a[i] = rand() % 1000;
	for (int i = 0; i < n; i++)
	{
		base = Insert(base, a[i], up, 0);
	} 
	initgraph(1200, 800);			// 创建绘图窗口
	settextstyle(16, 8, _T("黑体")); // 设置字体
	show(base, 0, 0, 1200);
	system("pause");
	closegraph();
}