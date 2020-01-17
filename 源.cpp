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

unsigned long long int ceil(unsigned long long int x)//[x/2]����ȡ��
{
	return (x - 1) / 2 + 1;
}

unsigned long long int Binary_search(const vector<pair<Node *, int>> &x, const int &t, unsigned long long int l, unsigned long long int r)//O(log(x.size()))
{//���ֲ��ң�ֻȷ����Χ������һ����t��������������������С�ڵ��������±���������һ��������Ǵ�������Ԫ�أ��������һ��Ԫ�ص��±�
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
	cout << layer << "��: ";
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
	unsigned long long int pos = Binary_search(x->data, t, 0, x->data.size() - 1);//���ֲ���
	if (x->data[pos].second == t)//�����Ѿ������ֵ��ֱ�ӷ���
	{
		return x;
	}
	if (x->end == nullptr)//���һ��
	{
		if (t > x->data[pos].second)pos++;//��������������е�Ԫ�أ�����뵽���
		x->data.insert(x->data.begin() + pos, make_pair(nullptr, t));
	}
	else {
		if (t < x->data[pos].second)
		{
			x->data[pos].first = Insert(x->data[pos].first, t, up, layer + 1);//�ݹ����
		}
		else if (t > x->data[pos].second)
		{
			x->end = Insert(x->end, t, up, layer + 1);
		}
	}
	if (up.first != nullptr)//�鿴�Ƿ���Ҫ��������Ԫ��
	{
		if (up.second > x->data[pos].second)pos++;
		x->data.insert(x->data.begin() + pos, up);
		up.first = nullptr;
	}
	if (x->data.size() == M)//���϶�
	{
		int mid = M / 2;
		if (layer == 0)//���ڵ����
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
		if (x->end == nullptr)//ɾ������Ҷ�ڵ�
		{
			x->data.erase(x->data.begin() + pos);
		}
		else {//��Ҷ�ڵ�
			// ���ý��Ϊ��Ҷ��㣬�ұ�ɾ�ؼ���Ϊ�ý���е�i���ؼ���key[i]����ɴ�ָ��son[i]��ָ���������ҳ���С�ؼ���Y������key[i]��λ�ã�Ȼ����Ҷ�����ɾȥY
			if (pos < x->data.size() - 1)
			{
				int del = x->data[pos + 1].first->data.front().second;
				x->data[pos].second = del;//�����������ô��?
				x->data[pos + 1].first = Delete(x->data[pos + 1].first, del, flag);
			}
			else {
				int del = x->end->data.front().second;
				x->data[pos].second = del;//�����������ô��?
				x->end = Delete(x->end, del, flag);
			}
		}
	}
	else if (x->end == nullptr)
	{
		cout << "δ�ҵ��ýڵ�" << endl;
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
			if (size == 1)//ֻ���ܳ�����M=3��ʱ��
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
			else {//0��λֻ�����ֵ�
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
		else if (pos == size - 1)//ֻ�����ֵ�
		{
			if (t > x->data[pos].second)//endɾ��
			{
				if (!x->data[pos].first && x->data[pos].first->data.size() >= ceil(M))//�鿴�����ڶ����Ƿ���Զ���ȥ
				{//���ԵĻ������һ������ȥ
					x->end->data.emplace_back(nullptr, x->data[pos].second);
					x->data[pos].second = x->data[pos].first->data[x->data[pos].first->data.size() - 1].second;
					x->data[pos].first->data.pop_back();
					flag = 0;
					return x;
				}
			}
			else {//�����ڶ���ɾ�������ֵ���end��
				if (!x->data[pos - 1].first && x->data[pos - 1].first->data.size() >= ceil(M))
				{
					x->data[pos - 1].first->data.emplace_back(nullptr, x->data[pos - 1].second);
					x->data[pos - 1].second = x->data[pos - 1].first->data[x->data[pos - 1].first->data.size() - 1].second;
					x->data[pos - 1].first->data.pop_back();
					flag = 0;
					return x;
				}
				else if (!x->end && x->end->data.size() >= ceil(M))//�����ֵ�end����
				{
					x->data[pos].first->data.emplace_back(nullptr, x->data[pos].second);
					x->data[pos].second = x->end->data[0].second;
					x->end->data.erase(x->end->data.begin());
					flag = 0;
					return x;
				}
			}
		}
		else {//���Ҷ����ֵ�
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
	if (flag)//�����ֵ�û�п��Ի��Ľڵ㣬���������ȥ�ϲ�
	{
		if (pos == size - 1)//pos-1��end�ϲ�
		{
			x->data[pos].first->data.emplace_back(x->data[pos].first->end, x->data[pos].second);
			copy(x->end->data.begin(), x->end->data.end(), insert_iterator<vector<pair<Node *, int>>>(x->data[pos].first->data, x->data[pos].first->data.end()));
			x->data[pos].first->end = x->end->end;
			delete x->end;
			x->end = x->data[pos].first;
			x->data.erase(x->data.begin() + pos);
			if (x->data.empty())//���ﲻʣԪ����
			{
				Node *ret = x->data[pos].first;
				flag = 0;
				delete x;
				return ret;
			}
		}
		else {//pos��pos+1�ϲ�
			x->data[pos].first->data.emplace_back(x->data[pos].first->end, x->data[pos].second);
			copy(x->data[pos + 1].first->data.begin(), x->data[pos + 1].first->data.end(), insert_iterator<vector<pair<Node *, int>>>(x->data[pos].first->data, x->data[pos].first->data.end()));
			x->data[pos].first->end = x->data[pos + 1].first->end;
			delete x->data[pos + 1].first;
			x->data[pos + 1].first = x->data[pos].first;
			x->data.erase(x->data.begin() + pos);
			if (x->data.empty())//���ﲻʣԪ����
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
	//�����ж��Ƿ�������
	if (x->data.size() < ceil(M) - 1)//����
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
		settextstyle(2 * radius, 0, _T("����"));
		outtextxy(nodes[k][0] + radius + 1, nodes[k][1] - radius, s);
		setlinecolor(YELLOW);
		if (nodes[2 * k][2] == 1)
			line(nodes[k][0], nodes[k][1] + radius, nodes[2 * k][0], nodes[2 * k][1] - radius);
		if (nodes[2 * k + 1][2] == 1)
			line(nodes[k][0], nodes[k][1] + radius, nodes[2 * k + 1][0], nodes[2 * k + 1][1] - radius);
		//Draw(T->Right, nodes, radius, 2 * k + 1);
	}
}

void show_node(int left, int top, int right, Node *t)//��ָ��λ�����һ���ڵ�
{
	TCHAR s[5];//�������
	int y = top + 20;
	int x = (left + right) / 2 - (3 * t->data.size() + 1) * 7.5;//��ʼλ��
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
	//����Ϊ������ɲ���
	show_node(left, top, right, T);
	//����Ϊ�����֧����
	if (T->end != nullptr)
	{
		int size = 1;
		for (const auto &x : T->data)
		{
			if (x.first != nullptr)size++;//sizeֻ��ʾ������������Ҫ����Ľڵ�ĸ���
		}
		step = (right - left) / size;
		x = (left + right + 1) / 2 - (3 * size + 1) * 7.5;//��ʼλ��
		for (const auto &y: T->data)
		{
			if (y.first != nullptr)
			{
				show(y.first, left + i * step, top + 60, left + (i + 1)*step);//�����ǰ�ڵ�
				line(x + 30 + i * 45, top + 30, left + (2 * i + 1)*step / 2, top + 80);//����
				i ++;
			}
		}
		show(T->end, left + i * step, top + 60, left + (i + 1)*step);//�����ǰ�ڵ�
		line(x + 30 + i * 45, top + 30, left + (2 * i + 1)*step / 2, top + 80);//����
	}
}

int main()
{
	Node *base = nullptr;
	pair<Node *, int> up;
	up.first = nullptr;
	int a[10010] = {};
	int n = 0;
	cout << "������B-������M: ";
	cin >> M;
	cout << "���������ݹ�ģn: ";
	cin >> n;
	for (int i = 0; i < n; i++)a[i] = rand() % 1000;
	for (int i = 0; i < n; i++)
	{
		base = Insert(base, a[i], up, 0);
	} 
	initgraph(1200, 800);			// ������ͼ����
	settextstyle(16, 8, _T("����")); // ��������
	show(base, 0, 0, 1200);
	system("pause");
	closegraph();
}