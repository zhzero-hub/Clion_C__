#include<iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

typedef struct 
{
	char name[10];
	char birth[12];
	int marriage;
	char address[50];
	int health;
	char death[12];
}ElemType;
typedef struct CSNode 
{
	ElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

int N, all;

void Create_(CSTree &T, FILE *fp)
{
	ElemType p;
	if(fread(&p, sizeof(ElemType), 1, fp) != 0)
    {
		if(strcmp(p.name, "0") == 0)
			T = NULL;
		else
        {
			T = (CSTree)malloc(sizeof(CSNode));
			T->data = p;
			Create_(T->firstchild, fp);
			Create_(T->nextsibling, fp);
		}
	}
}
int Create(CSTree &T, FILE *fp)
{
	int n, i;
	CSTree p;
	cout<<"请输入n:";
	cin>>n;
	p = (CSTree) malloc (sizeof(CSNode));
	if(!p) 
        exit(0);
	for(i = 0; i < n; i++)
    {
		cout<<i+1;
		cout<<"姓名:";
		cin>>p->data.name;
		cout<<"出生日期:";
		cin>>p->data.birth;
		cout<<"婚否:";
		cin>>p->data.marriage;
		cout<<"地址:";
		cin>>p->data.address;
		cout<<"健在否:";
		cin>>p->data.health;
		cout<<"死亡日期:";
		cin>>p->data.death;
		system("cls");
		fwrite(&p->data, sizeof(ElemType), 1, fp);
	}
}

void Print(CSTree T)  //输出成员的信息 
{
	cout<<endl;
    cout<<"姓名："<<T->data.name<<endl;
	cout<<"出生日期："<<T->data.birth<<endl;
	cout<<"婚否：";
	if(T->data.marriage) 
        cout<<"已婚"<<endl;
	else cout<<"未婚"<<endl;
	cout<<"地址："<<T->data.address<<endl;
	cout<<"健在否：";
	if(T->data.health) 
        cout<<"是"<<endl;
	else
    {
		cout<<"否";
		cout<<"死亡日期："<<T->data.death<<endl;
	} 
} 

void Show_gen(CSTree T, int m)  //输出第n代人的所有信息 
{
	if(m == N)
		while(T)
        {
			Print(T);
			T = T->nextsibling;
		}
	else
		while(T)
        {
			if(T->firstchild) 
                Show_gen(T->firstchild, m+1);
			T = T->nextsibling;
		}
}

void Show_n(CSTree T, int m, int &j, int N2)  //输出第n代人的所有信息 
{
	if(m == N2)
		while(T)
        {
			j++;
			cout<<T->data.name;
			T = T->nextsibling;
		}
	else
		while(T)
        {
			if(T->firstchild) 
                Show_n(T->firstchild, m+1, j, N2);
			T = T->nextsibling;
		}
}

void Pre(CSTree T)  //计算家谱中的总人数 
{
	if(T)
    {
		all++;
		Pre(T->firstchild);
		Pre(T->nextsibling);
	}
}

void Show(CSTree T)  //显示家谱 
{
	int j = 0, num = 0;
	int N2 = 1;
	all = 0;
	Pre(T);
	for(int i = 0; i < 10 && num < all; i++, N2++)
    {
		cout<<"第"<<i+1<<"代:";
		j = 0;
		Show_n(T, 1, j, N2);
		num=num+j;
		cout<<endl;
	}
}

void Find_gen(CSTree T, char na[10], int &m, int i)
{
	if(T)
    {
		if(strcmp(T->data.name, na) == 0)
			m = i;
		Find_gen(T->nextsibling, na, m, i);
		Find_gen(T->firstchild, na, m, i+1);
	}
}

void input(CSTree T, FILE *fp) //将修改后的信息重新存入文件
{
	ElemType p;   //设空 
	strcpy(p.name, "0");
	p.health = p.marriage = 0;
	strcpy(p.address, "0");
	strcpy(p.death, "0");
	strcpy(p.birth, "0");
	if(!T)
		fwrite(&p, sizeof(ElemType), 1, fp);
	else
    {
		fwrite(&T->data, sizeof(ElemType), 1, fp);
		input(T->firstchild, fp);
		input(T->nextsibling, fp);
	}
} 

int menu()
{
	int choose;
	cout<<"1.以图形方式显示家谱"<<endl;
	cout<<"2.显示第n 代所有人的信息"<<endl;
	cout<<"3.按照姓名查询"<<endl;
	cout<<"4.按照出生日期查询"<<endl;
	cout<<"5.确定两人关系"<<endl;
	cout<<"6.某成员添加孩子"<<endl;
	cout<<"7.删除某成员"<<endl;
	cout<<"8.修改成员信息"<<endl;
	cout<<"9.退出"<<endl;
    cout<<"您的选择；";
	cin>>choose;
	while(choose < 1 || choose >9)
    {
		cout<<"输入不合法！";
		cin>>choose;
	}
	return choose;
}

void PreOrder_(CSTree T, CSTree &p, char na[10])   //利用先序遍历根据姓名查找 
{
	if(T)
    {
		if(strcmp(T->data.name, na) == 0)
			p = T;
		PreOrder_(T->firstchild, p, na);
		PreOrder_(T->nextsibling, p, na);
	}
}

void PreOrder_Birth(CSTree T, CSTree &p, char bir[12])
{
	if(T)
    {
		if(strcmp(T->data.birth, bir) == 0)
			p = T;
		else
        {
			PreOrder_Birth(T->firstchild, p, bir);
			PreOrder_Birth(T->nextsibling, p, bir);
		}
	}
}

void Find_Parent(CSTree T, CSTree &p, CSTree &f, char na[10])   //找该成员的父亲 
{
	CSTree c;
	if(T)
    {
		for(c = T->firstchild; c; c = c->nextsibling)
			if(strcmp(c->data.name, na) == 0)
            {
				p = c;
				f = T;
				break;
			}
		Find_Parent(T->firstchild, p, f, na);
		Find_Parent(T->nextsibling, p, f, na);
	} 
}

void Del(CSTree &p)  //删除p结点的所有子树 
{
	CSTree c1, c2;
	if(p)
    {
		c1 = p->firstchild;
		c2 = p->nextsibling;
		free(p);
		Del(c1);
		Del(c2);
	}
}

int Delete_(CSTree &T)   //删除成员及其后代 
{
	CSTree p, f, c;
	p = f = NULL;
	char na[10];
	cout<<"姓名：";
	cin>>na;
	PreOrder_(T, p, na);
	if(!p)
    {
		cout<<"未找到该成员!";
		return 0;
	}
	else
    {
		Find_Parent(T, p, f, na);   //f为被删除结点的双亲结点 
		if(!f) 
            T = NULL;  //删除的是根结点 
		else
        {
			c = p;
			Del(p->firstchild);
			p = f->firstchild;
			if(p == c) 
                f->firstchild = NULL;
			else
            {
				while(p->nextsibling != c)
					p = p->nextsibling;
				p->nextsibling = c->nextsibling; 
			}   
			free(c);                           
		} 
	}
}

int Query_Birth(CSTree T)  //按照出生日期查询 
{
	CSTree p;
	p = NULL;
	char bir[12];
	cout<<"日期: ";
	cin>>bir;
	PreOrder_Birth(T, p, bir);
	if(!p)
    {
		cout<<"未找到该成员！";
		return 0;
	}
	else
		Print(p);
}

int Query_Name(CSTree T)  //按照姓名查询 
{
	CSTree p, f, c;
	int flag;
	p = f = NULL;
	char na[10];
	cout<<"姓名：";
	cin>>na;
	PreOrder_(T, p, na); //递归查找
	if(!p)
    {
		cout<<"未找到该成员!";
		return 0;
	} 
	else{
		cout<<"本人信息：";
		Print(p);  //输出该成员的信息 
		Find_Parent(T, p, f, na);
		cout<<"父亲的信息：";
		if(f)
			Print(f);
		else cout<<"无！";
		cout<<"孩子信息：";
		c = p->firstchild;
		flag = 0;
		while(c)
        {
			flag = 1;
			Print(c);
			cout<<"";
			c = c->nextsibling;
		}
		if(!flag) 
            cout<<"无！";
	}
}

int Add_Child(CSTree &T)  //添加一个孩子 
{
	CSTree f, child, p;  //父亲结点 
	char f_name[10]; 
	cout<<"请输入父亲的姓名：";
	cin>>f_name;
	PreOrder_(T, f, f_name);
	if(!f)
    {
		cout<<"未找到该父亲的信息!";
		return 0;
	}
	else
    {
		cout<<"请输入孩子的信息：";
		child = (CSTree) malloc (sizeof(CSNode));
		if(!child) exit(0);
		cout<<"姓名：";
		cin>>child->data.name;
		cout<<"出生日期：";
		cin>>child->data.birth;
		cout<<"地址：";
		cin>>child->data.address;
		child->data.health = 1;
		child->data.marriage = 0;
		strcpy(child->data.death, "无");
		if(!f->firstchild)
        {
			f->firstchild = child;
			child->firstchild = child->nextsibling = NULL;
		}
		else
        {
			p = f->firstchild;
			while(p->nextsibling){
				p = p->nextsibling;
			}
			p->nextsibling = child;
			child->nextsibling = child->firstchild = NULL;
		}
	}
} 

int Modify(CSTree &T)  //修改成员的信息 
{
	CSTree p;
	p = NULL;
	char na[10];
	int choose;
	cout<<"请输入要修改的成员的姓名：";
	cin>>na;
	PreOrder_(T, p, na);
	if(!p) 
    {
		cout<<"未找到该成员！";
		return 0;
	}
	else
    {
		cout<<"1.姓名";
		cout<<"2.出生日期";
		cout<<"3.婚否";
		cout<<"4.地址";
		cout<<"5.健在否";
		cout<<"6.死亡日期";
		cout<<"您的选择：";
		cin>>choose;
		while(choose < 1 || choose > 6)
        {
			cout<<"输入不合法！";
			cin>>choose;
		}
		switch(choose)
        {
			case 1:
				cout<<"请输入新的姓名：";
				cin>>p->data.name;
				break;
			case 2:
				cout<<"请输入新的出生日期：";
				cin>>p->data.birth;
				break;
			case 3:
				cout<<"请输入新的婚姻情况(0-未婚,1-已婚):";
				cin>>p->data.marriage;
				break; 
			case 4:
				cout<<"请输入新的地址：";
				cin>>p->data.address;
				break;
			case 5:
				cout<<"请输入新的健在情况(0-死亡,1-健在)：";
				cin>>p->data.health;
				if(!p->data.health)
                {
					cout<<"请输入死亡日期：";
					cin>>p->data.death;
				}
				break;
			case 6:
				cout<<"请输入新的死亡日期: ";
				cin>>p->data.death;
				break;
		}
		cout<<"修改后该成员的信息：";
		Print(p);
	}
}

int Relationship(CSTree T)
{
	char name1[10], name2[10];
	CSTree f1, f2, p1, p2, g1, g2;
	int gen1, gen2;
	gen1 = gen2 = 0;
	p1 = p2 = NULL;
	cout<<"请输入第一个人的姓名：";
	cin>>name1;
	cout<<"请输入第二个人的姓名：";
	cin>>name2;
	Find_Parent(T, p1, f1, name1);  //找到两人的父亲 
	Find_Parent(T, p2, f2, name2);
	Find_gen(T, name1, gen1, 1);  //判断两个人的代数 
	Find_gen(T, name2, gen2, 1);
	if(f1 == f2)
        cout<<"亲兄弟";
	else if(gen1 == gen2) 
        cout<<"堂兄弟";
	else if(fabs(gen1 - gen2) == 1)
    {
		if(p1 == f2 || p2 == f1) 
            cout<<"父子";
		else 
            cout<<"叔侄";
	}
	else if(fabs(gen1 - gen2) == 2)
    {
		Find_Parent(T, f1, g1, f1->data.name);
		Find_Parent(T, f2, g2, f2->data.name);
		if(g1 == p2 || g2 == p1) 
            cout<<"爷孙";
		else 
            cout<<"叔祖父";
	}
	else 
        cout<<"曾祖父";
}

int main()
{
	CSTree T;
	ElemType p;
	char na[10];
	int choose;
	FILE *fp = fopen("家谱.dat", "rb");
	Create_(T, fp);  //从文件中读取信息并构建以孩子兄弟表示的树 
	fclose(fp);
	while(true)
    {
		system("cls");
		choose = menu();
		switch(choose)
        {
			case 1: //以图形方式显示家谱 
				system("cls");
				Show(T);
				system("pause");
				break;
			case 2: //显示第n代所有人的信息 
				system("cls");
				cout<<"请输入n:";
				cin>> N; 
				Show_gen(T, 1);
				system("pause");
				break;
			case 3:  //按照姓名查询
				system("cls"); 
				Query_Name(T);
				system("pause");
				break;
			case 4:  //按照出生日期查询 
				system("cls");
				Query_Birth(T);
				system("pause");
				break;
			case 5:  //确定两人关系 
				system("cls");
				Relationship(T);
				system("pause");
				break;
			case 6:  //某成员添加孩子 
				system("cls");
				Add_Child(T); 
				fp = fopen("3.dat", "wb");
				input(T, fp);  //将改写后的文件重新写入文件 
				fclose(fp);
				system("pause");
				break;
			case 7:  //删除某成员 
				system("cls");
				Delete_(T);
				system("pause");
				fp = fopen("3.dat", "wb");
				input(T, fp);  //将改写后的文件重新写入文件 
				fclose(fp);
				break;
			case 8:  //修改成员信息 
				system("cls");
				Modify(T);
				system("pause");
				fp = fopen("3.dat", "wb");
				input(T, fp);  //将改写后的文件重新写入文件 
				fclose(fp);
				break;
			case 9:
				return 0;
		}
	}
}

