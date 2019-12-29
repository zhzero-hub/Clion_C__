//
// Created by Z_HAO on 2019/11/27.
//

#include <iostream>
#include <graphics.h>
#include <conio.h>
using namespace std;

struct Node
{
	int data = 0;
	Node *l = nullptr;
	Node *r = nullptr;
	int h = 0;
};

struct Tree
{
	Node *base = nullptr;
};

int MAX(int a, int b)
{
	if (a > b)return a;
	else return b;
}

int Gethight(Node *x)
{
	if (x == nullptr || (x->l == nullptr && x->r == nullptr))return 0;
	else
	{
		return MAX(Gethight(x->l), Gethight(x->r)) + 1;
	}
}

Node *RR_rotation(Node *x)
{
	Node *p = x->r;
	x->r = p->l;
	p->l = x;
	x->h = MAX(Gethight(x->l), Gethight(x->r)) + 1;
	p->h = MAX(Gethight(p->l), x->h) + 1;
	return p;
}

Node *LL_rotation(Node *x)
{
	Node *p = x->l;
	x->l = p->r;
	p->r = x;
	x->h = MAX(Gethight(x->l), Gethight(x->r)) + 1;
	p->h = MAX(Gethight(p->l), x->h) + 1;
	return p;
}

Node *LR_rotation(Node *x)
{
	x->l = RR_rotation(x->l);
	return LL_rotation(x);
}

Node *RL_rotation(Node *x)
{
	x->r = LL_rotation(x->r);
	return RR_rotation(x);
}

Node *Ballance_insert(Node *x, int t)
{
	if (x == nullptr)
	{
		x = (Node *)malloc(sizeof(Node));
		x->data = t;
		x->l = x->r = nullptr;
		x->h = 0;
		return x;
	}
	else
	{
		if (t == x->data)
		{
			return x;
		}
		else if (t < x->data)
		{
			x->l = Ballance_insert(x->l, t);
			if (Gethight(x->l) - Gethight(x->r) == 2)
			{
				if (t < x->l->data)//LL
				{
					x = LL_rotation(x);
				}
				else
				{
					x = LR_rotation(x);
				}
			}
		}
		else if(t > x->data)
		{
			x->r = Ballance_insert(x->r, t);
			if (Gethight(x->l) - Gethight(x->r) == -2)
			{
				if (t > x->r->data)//RR
				{
					x = RR_rotation(x);
				}
				else
				{
					x = RL_rotation(x);
				}
			}
		}
	}
	x->h = MAX(Gethight(x->l), Gethight(x->r)) + 1;
	return x;
}

void newnode(Tree &x, int t)
{
	x.base = (Node *)malloc(sizeof(Node));
	x.base->data = t;
	x.base->l = nullptr;
	x.base->r = nullptr;
}

Node *Findmin(Node *x)
{
	Node *p = x;
	while (p->l != nullptr)p = p->l;
	return p;
}

Node *Findmax(Node *x)
{
	Node *p = x;
	while (p->r != nullptr)p = p->r;
	return p;
}

Node *Delete(Node *x, int t)
{
	if (x == nullptr)return x;
	if (t < x->data)
	{
		x->l = Delete(x->l, t);
		if (Gethight(x->r) - Gethight(x->l) >= 2)
		{
			if (Gethight(x->r->r) - Gethight(x->r->l) >= 2)
			{
				x = RR_rotation(x);
			}
			else
			{
				x = RL_rotation(x);
			}
		}
		x->h = MAX(Gethight(x->l), Gethight(x->r)) + 1;
	}
	else if (t > x->data)
	{
		x->r = Delete(x->r, t);
		if (Gethight(x->l) - Gethight(x->r) >= 2)
		{
			if (Gethight(x->l->l) - Gethight(x->l->r) >= 2)
			{
				x = LL_rotation(x);
			}
			else
			{
				x = LR_rotation(x);
			}
		}
		x->h = MAX(Gethight(x->l), Gethight(x->r)) + 1;
	}
	else
	{
		if (x->l != nullptr && x->r != nullptr)
		{
			if (Gethight(x->l) < Gethight(x->r))
			{
				Node *temp = Findmin(x->r);
				x->data = temp->data;
				x->r = Delete(x->r, x->data);
			}//右子树更高，从右子树删除
			else
			{
				Node *temp = Findmax(x->l);
				x->data = temp->data;
				x->l = Delete(x->l, x->data);
			}
		}
		else if (x->l == nullptr)
		{
			Node *temp = x;
			x = x->r;
			free(temp);
		}
		else if (x->r == nullptr)
		{
			Node *temp = x;
			x = x->l;
			free(temp);
		}
	}
	return x;
}

void in_order(Node *node)
{
	if (node != nullptr)
	{
		in_order(node->l);
		cout << node->data << ' ';
		in_order(node->r);
	}
}

void show_node(int left, int top, int right, Node *t)//在指定位置输出一个节点
{
	TCHAR s[5];//用于临时存储
	// ttextstyle(6, 5, _T("黑体"));
	int size = 1;
	int y = top + 20;
	int x = (left + right) / 2 - (3 * size + 1) * 7.5;//总宽度
	rectangle(x, y, x + (3 * size + 1) * 15, y + 20);
	int i = 0;
	_stprintf_s(s, _T("%d"), t->data);
	outtextxy(x + 21 + 45 * i, y + 4, s);
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
	if (T->l != nullptr || T->r!= nullptr)
	{
		int size = 2;
		step = (right - left) / size;
		x = (left + right + 1) / 2 - (3 * size + 1) * 7.5;//起始位置
		if (T->l != nullptr)
		{
			show(T->l, left + i * step, top + 60, left + (i + 1)*step);
			line(x + 30 + i * 45, top + 30, left + (2 * i + 1)*step / 2, top + 80);//画线
		}
		i ++;
		if (T->r != nullptr)
		{
			show(T->r, left + i * step, top + 60, left + (i + 1)*step);
			line(x + 30 + i * 45, top + 30, left + (2 * i + 1)*step / 2, top + 80);//画线
		}
	}
}

int main()
{
	int n;
	Tree tree;
	cout << "请输入数据规模: ";
	cin >> n;
	int a[10010] = {};
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 1000;
		tree.base = Ballance_insert(tree.base, a[i]);
	}
	initgraph(1200, 800);			// 创建绘图窗口
	settextstyle(16, 8, _T("黑体")); // 设置字体
	show(tree.base, 0, 0, 1200);
	system("pause");
}