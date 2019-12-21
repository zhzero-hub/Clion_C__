#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

struct Node
{
	char name[10];//姓名
	char birth[12];//出生日期
	int marriage;//婚否
	Node *couple = nullptr;
	char address[50];//地址
	int health;//是否健在
	char death[12];//死亡日期
};

struct CSNode//孩子兄弟树
{
	Node data;
	CSNode *fir = nullptr , *sib = nullptr;
};

int N , all;

void Create(CSNode * &T , FILE *fp)
{
    T = (CSNode *)malloc(sizeof(CSNode));
    if(fread(T , sizeof(Node) , 1 , fp) != 0)
    {
		if(strcmp(T->data.name , "0") == 0) {
            free(T);
            T = nullptr;
        }
		else
        {
			T = (CSNode *)malloc(sizeof(CSNode));
			if(T->data.marriage) {
                fread(T->data.couple , sizeof(Node) , 1 , fp);
			}
			else T->data.couple = nullptr;
			Create(T->fir , fp);//递归读取信息
			Create(T->sib , fp);
		}
	}
}

int Initiate(CSNode * &T, FILE *fp)
{
	int n , i;
	CSNode *p = (CSNode *)malloc(sizeof(CSNode));
	CSNode *q = nullptr;
	cout << "请输入n:";
	cin >> n;
	for(i = 0; i < n; i++)
    {
		cout << i + 1;
		cout << "姓名: ";
		cin >> p->data.name;
		cout << "出生日期: ";
		cin >> p->data.birth;
		cout << "婚否: ";
		cin >> p->data.marriage;
		if(p->data.marriage) {
            q = (CSNode *)malloc(sizeof(CSNode));
            cout << i + 1;
            cout << "姓名: ";
            cin >> q->data.name;
            cout << "出生日期: ";
            cin >> q->data.birth;
            q->data.marriage = 1;
            cout << "地址: ";
            cin >> q->data.address;
            cout << "健在否: ";
            cin >> q->data.health;
            cout << "死亡日期: ";
            cin >> q->data.death;
            p->data.couple = &q->data;
            q->data.couple = &p->data;
            system("cls");
		}
		cout << "地址: ";
		cin >> p->data.address;
		cout << "健在否: ";
		cin >> p->data.health;
		cout << "死亡日期: ";
		cin >> p->data.death;
		system("cls");
		fwrite(&p->data, sizeof(Node), 1, fp);
        if(q)fwrite(&q->data, sizeof(Node), 1, fp);
	}
	return 1;
}

void Print(Node *T)  //输出成员的信息
{
	cout << endl;
    cout << "姓名：" << T->name << endl;
	cout << "出生日期：" << T->birth << endl;
	cout << "婚否：";
	if(T->marriage){
        cout << "已婚" << endl;
        cout << "配偶信息为: " << endl;
        Print(T->couple);
	}
	else cout << "未婚" << endl;
	cout << "地址：" << T->address << endl;
	cout << "健在否：";
	if(T->health)
        cout << "是" << endl;
	else
    {
		cout << "否";
		cout << "死亡日期：" << T->death << endl;
	} 
} 

void Show_gen(CSNode * T, int m)  //输出第n代人的所有信息 
{//需要做图形化处理
	if(m == N)
    {
        while(T)
        {
            Print(&T->data);
            T = T->sib;
        }
    }
	else
    {
        while(T)
        {
            if(T->fir)
                Show_gen(T->fir, m + 1);
            T = T->sib;
        }
    }
}

void Show_n(CSNode * T, int m, int &j, int N2)  //输出第n代人的所有信息 
{
	if(m == N2)
    {
        while(T)
        {
            j ++;
            cout << T->data.name;
            T = T->sib;
        }
    }
	else
    {
        while(T)
        {
            if(T->fir)
                Show_n(T->fir, m + 1, j, N2);
            T = T->sib;
        }
    }
}

void Pre(CSNode * T)  //计算家谱中的总人数 
{
	if(T)
    {
		all ++;
		Pre(T->fir);
		Pre(T->sib);
	}
}

void Show(CSNode * T)  //显示家谱 
{
	int j = 0, num = 0;
	int N2 = 1;
	all = 0;
	Pre(T);
	for(int i = 0; i < 10 && num < all; i++, N2++)
    {
		cout << "第" << i + 1 << "代: ";
		j = 0;
		Show_n(T, 1, j, N2);
		num = num + j;
		cout << endl;
	}
}

void Find_gen(CSNode * T, char na[], int &m, int i)
{
	if(T)
    {
		if(strcmp(T->data.name, na) == 0)
			m = i;
		Find_gen(T->sib, na, m, i);
		Find_gen(T->fir, na, m, i + 1);
	}
}

void input(CSNode * T, FILE *fp) //将修改后的信息重新存入文件
{
	Node p{};   //设空
	strcpy(p.name, "0");
	p.health = p.marriage = 0;
	strcpy(p.address, "0");
	strcpy(p.death, "0");
	strcpy(p.birth, "0");
	if(!T)
		fwrite(&p, sizeof(Node), 1, fp);
	else
    {
		fwrite(&T->data, sizeof(Node), 1, fp);
		input(T->fir, fp);
		input(T->sib, fp);
	}
} 

int menu()
{
	int choose;
	cout << "1.以图形方式显示家谱" << endl;
	cout << "2.显示第n 代所有人的信息" << endl;
	cout << "3.按照姓名查询" << endl;
	cout << "4.按照出生日期查询" << endl;
	cout << "5.确定两人关系" << endl;
	cout << "6.某成员添加孩子" << endl;
	cout << "7.删除某成员" << endl;
	cout << "8.修改成员信息" << endl;
	cout << "9.退出" << endl;
    cout << "您的选择: ";
	cin >> choose;
	while(choose < 1 || choose > 9)
    {
		cout << "输入不合法！";
		cin >> choose;
	}
	return choose;
}

void PreOrder(CSNode * T, CSNode * &p, char na[])   //利用先序遍历根据姓名查找
{
	if(T)
    {
		if(strcmp(T->data.name, na) == 0)
			p = T;
		PreOrder(T->fir, p, na);
		PreOrder(T->sib, p, na);
	}
}

void PreOrder_Birth(CSNode * T, CSNode * &p, char bir[])
{
	if(T)
    {
		if(strcmp(T->data.birth, bir) == 0)
			p = T;
		else
        {
			PreOrder_Birth(T->fir, p, bir);
			PreOrder_Birth(T->sib, p, bir);
		}
	}
}

void Find_Parent(CSNode *T, CSNode *&p, CSNode *&f, char na[])   //找该成员的父亲
{
	CSNode *c;
	if(T)
    {
		for(c = T->fir;c != nullptr;c = c->sib)
        {
            if(strcmp(c->data.name, na) == 0 || strcmp(c->data.couple->name, na) == 0)
            {
                p = c;
                f = T;
                return;
            }
        }
		Find_Parent(T->fir, p, f, na);
		Find_Parent(T->sib, p, f, na);
	} 
}

void Del(CSNode * &p)  //删除p结点的所有子树 
{
	CSNode *c1 , *c2;
	if(p)
    {
		c1 = p->fir;
		c2 = p->sib;
		free(p);
		Del(c1);
		Del(c2);
	}
}

void Delete(CSNode * &T)   //删除成员及其后代
{
	CSNode *p, *f, *c;
	p = f = nullptr;
	char na[10];
	cout << "姓名: ";
	cin >> na;
	PreOrder(T, p, na);
	if(!p)
    {
		cout << "未找到该成员!" << endl;
		return;
	}
	else
    {
		Find_Parent(T, p, f, na);   //f为被删除结点的双亲结点 
		if(f == nullptr)//T是根节点
            T = nullptr;//删除的是根结点
		else
        {
			c = p;
			Del(p->fir);
			p = f->fir;
			if(p == c) 
                f->fir = nullptr;
			else
            {
				while(p->sib != c)
					p = p->sib;
				p->sib = c->sib;
			}   
			free(c);                           
		} 
	}
}

int Query_Birth(CSNode * T)  //按照出生日期查询 
{
	CSNode * p;
	p = nullptr;
	char bir[12];
	cout << "日期: ";
	cin >> bir;
	PreOrder_Birth(T, p, bir);
	if(!p)
    {
		cout<<"未找到该成员！" << endl;
		return 0;
	}
	else
		Print(&p->data);
}

void Query_Name(CSNode * T)  //按照姓名查询
{
	CSNode *p, *f, *c;
	int flag;
	p = f = nullptr;
	char na[10];
	cout << "姓名：";
	cin >> na;
	PreOrder(T, p, na); //递归查找
	if(p == nullptr)
    {
		cout << "未找到该成员!";
		return;
	} 
	else {
	    cout << "本人信息: " <<endl;
		Print(&p->data);  //输出该成员的信息
		Find_Parent(T, p, f, na);
		cout << "父亲的信息：";
		if(f != nullptr)
			Print(&f->data);
		else cout << "无！" << endl;
		cout << "孩子信息: " << endl;
		c = p->fir;
		flag = 0;
		while(c)
        {
			flag = 1;
			Print(&c->data);
			c = c->sib;
		}
		if(!flag) 
            cout << "无！" << endl;
	}
}

void Add_Child(CSNode * &T)  //添加一个孩子
{
	CSNode * f, *child, *p;  //父亲结点
	char f_name[10]; 
	cout << "请输入父亲的姓名：";
	cin >> f_name;
	PreOrder(T, f, f_name);
	if(!f)
    {
		cout << "未找到该父亲的信息!" << endl;
		return;
	}
	else
    {
		cout << "请输入孩子的信息：";
		child = (CSNode *)malloc(sizeof(CSNode));
		if(!child)
        {
		    exit(0);
        }
		cout << "姓名: ";
		cin >> child->data.name;
		cout << "出生日期: ";
		cin >> child->data.birth;
		cout << "地址: ";
		cin >> child->data.address;
		child->data.health = 1;
		child->data.marriage = 0;
		strcpy(child->data.death , "\0");
		if(!f->fir)
        {
			f->fir = child;
            child->fir = child->sib = nullptr;
		}
		else
        {
			p = f->fir;
			while(p->sib != nullptr){
				p = p->sib;
			}
			p->sib = child;
            child->sib = child->fir = nullptr;
		}
	}
} 

int Modify(CSNode * &T)  //修改成员的信息 
{
	CSNode *p = nullptr;
	char na[10];
	int choose;
	cout << "请输入要修改的成员的姓名：";
	cin >> na;
	PreOrder(T, p, na);
	if(p == nullptr)
    {
		cout << "未找到该成员！" << endl;
		return 0;
	}
	else
    {
		cout << "1.姓名" << endl;
		cout << "2.出生日期" << endl;
		cout << "3.婚否" << endl;
		cout << "4.地址" << endl;
		cout << "5.健在否" << endl;
		cout << "6.死亡日期" << endl;
		cout << "您的选择: ";
		cin >> choose;
		while(choose < 1 || choose > 6)
        {
			cout << "输入不合法！";
			cin >> choose;
		}
		if(choose == 1) {
            cout << "请输入新的姓名: ";
            cin >> p->data.name;
        }
		else if(choose == 2) {
            cout << "请输入新的出生日期: ";
            cin >> p->data.birth;
        }
		else if(choose == 3) {
            cout << "请输入新的婚姻情况(0-未婚,1-已婚): ";
            cin >> p->data.marriage;
        }
		else if(choose == 4) {
            cout << "请输入新的地址: ";
            cin >> p->data.address;
        }
		else if(choose == 5) {
            cout << "请输入新的健在情况(0-死亡,1-健在): ";
            cin >> p->data.health;
            if (!p->data.health) {
                cout << "请输入死亡日期: ";
                cin >> p->data.death;
            }
        }
		else if(choose == 6) {
            cout << "请输入新的死亡日期: ";
            cin >> p->data.death;
        }
    }
	cout<<"修改后该成员的信息： " << endl;
	Print(&p->data);
	return 1;
}

void Relationship(CSNode * T)
{
	char name1[10], name2[10];
	CSNode * f1, *f2, *p1, *p2, *g1, *g2;
	int gen1, gen2;
	gen1 = gen2 = 0;
	p1 = p2 = nullptr;
	cout << "请输入第一个人的姓名：";
	cin >> name1;
	cout << "请输入第二个人的姓名：";
	cin >> name2;
	Find_Parent(T, p1, f1, name1);  //找到两人的父亲 
	Find_Parent(T, p2, f2, name2);
	Find_gen(T, name1, gen1, 1);  //判断两个人的代数 
	Find_gen(T, name2, gen2, 1);
	if(f1 == f2) {
        cout << "亲兄弟" << endl;
        return;
    }
	else if(gen1 == gen2) {
        cout << "堂兄弟" << endl;
        return;
	}
	else if(fabs(gen1 - gen2) == 1) {
		if(p1 == f2 || p2 == f1) {
            cout << "父子" << endl;
        }
		else {
            cout << "叔侄" << endl;
        }
		return;
	}
	else if(fabs(gen1 - gen2) == 2) {
		Find_Parent(T, f1, g1, f1->data.name);
		Find_Parent(T, f2, g2, f2->data.name);
		if(g1 == p2 || g2 == p1) 
            cout << "爷孙" << endl;
		else 
            cout << "叔祖父" << endl;
		return;
	}
	else if(fabs(gen1 - gen2) == 3) {
        cout << "曾祖父" << endl;
        return;
    }
	else cout << "不属于三代内的关系" << endl;
}

int main()
{
	CSNode *T;
	Node p;
	char na[10];
	int choose;
	FILE *fp = fopen("家谱.dat", "rb");
	Create(T, fp);  //从文件中读取信息并构建以孩子兄弟表示的树
	fclose(fp);
	while(true)
    {
		system("cls");
		choose = menu();
        if(choose == 1) {
            //以图形方式显示家谱
            system("cls");
            Show(T);
            system("pause");
        }
        else if(choose == 2) {
            //显示第n代所有人的信息
            system("cls");
            cout << "请输入n: ";
            cin >> N;
            Show_gen(T, 1);
            system("pause");
        }
		else if(choose == 3) {
            //按照姓名查询
            system("cls");
            Query_Name(T);
            system("pause");
        }
		else if(choose == 4) {
            //按照出生日期查询
            system("cls");
            Query_Birth(T);
            system("pause");
        }
		else if(choose == 5) {
            //确定两人关系
            system("cls");
            Relationship(T);
            system("pause");
        }
		else if(choose == 6) {
            //某成员添加孩子
            system("cls");
            Add_Child(T);
            fp = fopen("3.dat", "wb");
            input(T, fp);  //将改写后的文件重新写入文件
            fclose(fp);
            system("pause");
        }
		else if(choose == 7) {
            //删除某成员
            system("cls");
            Delete(T);
            system("pause");
            fp = fopen("3.dat", "wb");
            input(T, fp);  //将改写后的文件重新写入文件
            fclose(fp);
        }
		else if(choose == 8) {
            //修改成员信息
            system("cls");
            Modify(T);
            system("pause");
            fp = fopen("3.dat", "wb");
            input(T, fp);  //将改写后的文件重新写入文件
            fclose(fp);
        }
		else {
		    break;
		}
	}
}

