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
	cout<<"������n:";
	cin>>n;
	p = (CSTree) malloc (sizeof(CSNode));
	if(!p) 
        exit(0);
	for(i = 0; i < n; i++)
    {
		cout<<i+1;
		cout<<"����:";
		cin>>p->data.name;
		cout<<"��������:";
		cin>>p->data.birth;
		cout<<"���:";
		cin>>p->data.marriage;
		cout<<"��ַ:";
		cin>>p->data.address;
		cout<<"���ڷ�:";
		cin>>p->data.health;
		cout<<"��������:";
		cin>>p->data.death;
		system("cls");
		fwrite(&p->data, sizeof(ElemType), 1, fp);
	}
}

void Print(CSTree T)  //�����Ա����Ϣ 
{
	cout<<endl;
    cout<<"������"<<T->data.name<<endl;
	cout<<"�������ڣ�"<<T->data.birth<<endl;
	cout<<"���";
	if(T->data.marriage) 
        cout<<"�ѻ�"<<endl;
	else cout<<"δ��"<<endl;
	cout<<"��ַ��"<<T->data.address<<endl;
	cout<<"���ڷ�";
	if(T->data.health) 
        cout<<"��"<<endl;
	else
    {
		cout<<"��";
		cout<<"�������ڣ�"<<T->data.death<<endl;
	} 
} 

void Show_gen(CSTree T, int m)  //�����n���˵�������Ϣ 
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

void Show_n(CSTree T, int m, int &j, int N2)  //�����n���˵�������Ϣ 
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

void Pre(CSTree T)  //��������е������� 
{
	if(T)
    {
		all++;
		Pre(T->firstchild);
		Pre(T->nextsibling);
	}
}

void Show(CSTree T)  //��ʾ���� 
{
	int j = 0, num = 0;
	int N2 = 1;
	all = 0;
	Pre(T);
	for(int i = 0; i < 10 && num < all; i++, N2++)
    {
		cout<<"��"<<i+1<<"��:";
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

void input(CSTree T, FILE *fp) //���޸ĺ����Ϣ���´����ļ�
{
	ElemType p;   //��� 
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
	cout<<"1.��ͼ�η�ʽ��ʾ����"<<endl;
	cout<<"2.��ʾ��n �������˵���Ϣ"<<endl;
	cout<<"3.����������ѯ"<<endl;
	cout<<"4.���ճ������ڲ�ѯ"<<endl;
	cout<<"5.ȷ�����˹�ϵ"<<endl;
	cout<<"6.ĳ��Ա��Ӻ���"<<endl;
	cout<<"7.ɾ��ĳ��Ա"<<endl;
	cout<<"8.�޸ĳ�Ա��Ϣ"<<endl;
	cout<<"9.�˳�"<<endl;
    cout<<"����ѡ��";
	cin>>choose;
	while(choose < 1 || choose >9)
    {
		cout<<"���벻�Ϸ���";
		cin>>choose;
	}
	return choose;
}

void PreOrder_(CSTree T, CSTree &p, char na[10])   //����������������������� 
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

void Find_Parent(CSTree T, CSTree &p, CSTree &f, char na[10])   //�Ҹó�Ա�ĸ��� 
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

void Del(CSTree &p)  //ɾ��p������������ 
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

int Delete_(CSTree &T)   //ɾ����Ա������ 
{
	CSTree p, f, c;
	p = f = NULL;
	char na[10];
	cout<<"������";
	cin>>na;
	PreOrder_(T, p, na);
	if(!p)
    {
		cout<<"δ�ҵ��ó�Ա!";
		return 0;
	}
	else
    {
		Find_Parent(T, p, f, na);   //fΪ��ɾ������˫�׽�� 
		if(!f) 
            T = NULL;  //ɾ�����Ǹ���� 
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

int Query_Birth(CSTree T)  //���ճ������ڲ�ѯ 
{
	CSTree p;
	p = NULL;
	char bir[12];
	cout<<"����: ";
	cin>>bir;
	PreOrder_Birth(T, p, bir);
	if(!p)
    {
		cout<<"δ�ҵ��ó�Ա��";
		return 0;
	}
	else
		Print(p);
}

int Query_Name(CSTree T)  //����������ѯ 
{
	CSTree p, f, c;
	int flag;
	p = f = NULL;
	char na[10];
	cout<<"������";
	cin>>na;
	PreOrder_(T, p, na); //�ݹ����
	if(!p)
    {
		cout<<"δ�ҵ��ó�Ա!";
		return 0;
	} 
	else{
		cout<<"������Ϣ��";
		Print(p);  //����ó�Ա����Ϣ 
		Find_Parent(T, p, f, na);
		cout<<"���׵���Ϣ��";
		if(f)
			Print(f);
		else cout<<"�ޣ�";
		cout<<"������Ϣ��";
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
            cout<<"�ޣ�";
	}
}

int Add_Child(CSTree &T)  //���һ������ 
{
	CSTree f, child, p;  //���׽�� 
	char f_name[10]; 
	cout<<"�����븸�׵�������";
	cin>>f_name;
	PreOrder_(T, f, f_name);
	if(!f)
    {
		cout<<"δ�ҵ��ø��׵���Ϣ!";
		return 0;
	}
	else
    {
		cout<<"�����뺢�ӵ���Ϣ��";
		child = (CSTree) malloc (sizeof(CSNode));
		if(!child) exit(0);
		cout<<"������";
		cin>>child->data.name;
		cout<<"�������ڣ�";
		cin>>child->data.birth;
		cout<<"��ַ��";
		cin>>child->data.address;
		child->data.health = 1;
		child->data.marriage = 0;
		strcpy(child->data.death, "��");
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

int Modify(CSTree &T)  //�޸ĳ�Ա����Ϣ 
{
	CSTree p;
	p = NULL;
	char na[10];
	int choose;
	cout<<"������Ҫ�޸ĵĳ�Ա��������";
	cin>>na;
	PreOrder_(T, p, na);
	if(!p) 
    {
		cout<<"δ�ҵ��ó�Ա��";
		return 0;
	}
	else
    {
		cout<<"1.����";
		cout<<"2.��������";
		cout<<"3.���";
		cout<<"4.��ַ";
		cout<<"5.���ڷ�";
		cout<<"6.��������";
		cout<<"����ѡ��";
		cin>>choose;
		while(choose < 1 || choose > 6)
        {
			cout<<"���벻�Ϸ���";
			cin>>choose;
		}
		switch(choose)
        {
			case 1:
				cout<<"�������µ�������";
				cin>>p->data.name;
				break;
			case 2:
				cout<<"�������µĳ������ڣ�";
				cin>>p->data.birth;
				break;
			case 3:
				cout<<"�������µĻ������(0-δ��,1-�ѻ�):";
				cin>>p->data.marriage;
				break; 
			case 4:
				cout<<"�������µĵ�ַ��";
				cin>>p->data.address;
				break;
			case 5:
				cout<<"�������µĽ������(0-����,1-����)��";
				cin>>p->data.health;
				if(!p->data.health)
                {
					cout<<"�������������ڣ�";
					cin>>p->data.death;
				}
				break;
			case 6:
				cout<<"�������µ���������: ";
				cin>>p->data.death;
				break;
		}
		cout<<"�޸ĺ�ó�Ա����Ϣ��";
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
	cout<<"�������һ���˵�������";
	cin>>name1;
	cout<<"������ڶ����˵�������";
	cin>>name2;
	Find_Parent(T, p1, f1, name1);  //�ҵ����˵ĸ��� 
	Find_Parent(T, p2, f2, name2);
	Find_gen(T, name1, gen1, 1);  //�ж������˵Ĵ��� 
	Find_gen(T, name2, gen2, 1);
	if(f1 == f2)
        cout<<"���ֵ�";
	else if(gen1 == gen2) 
        cout<<"���ֵ�";
	else if(fabs(gen1 - gen2) == 1)
    {
		if(p1 == f2 || p2 == f1) 
            cout<<"����";
		else 
            cout<<"��ֶ";
	}
	else if(fabs(gen1 - gen2) == 2)
    {
		Find_Parent(T, f1, g1, f1->data.name);
		Find_Parent(T, f2, g2, f2->data.name);
		if(g1 == p2 || g2 == p1) 
            cout<<"ү��";
		else 
            cout<<"���游";
	}
	else 
        cout<<"���游";
}

int main()
{
	CSTree T;
	ElemType p;
	char na[10];
	int choose;
	FILE *fp = fopen("����.dat", "rb");
	Create_(T, fp);  //���ļ��ж�ȡ��Ϣ�������Ժ����ֵܱ�ʾ���� 
	fclose(fp);
	while(true)
    {
		system("cls");
		choose = menu();
		switch(choose)
        {
			case 1: //��ͼ�η�ʽ��ʾ���� 
				system("cls");
				Show(T);
				system("pause");
				break;
			case 2: //��ʾ��n�������˵���Ϣ 
				system("cls");
				cout<<"������n:";
				cin>> N; 
				Show_gen(T, 1);
				system("pause");
				break;
			case 3:  //����������ѯ
				system("cls"); 
				Query_Name(T);
				system("pause");
				break;
			case 4:  //���ճ������ڲ�ѯ 
				system("cls");
				Query_Birth(T);
				system("pause");
				break;
			case 5:  //ȷ�����˹�ϵ 
				system("cls");
				Relationship(T);
				system("pause");
				break;
			case 6:  //ĳ��Ա��Ӻ��� 
				system("cls");
				Add_Child(T); 
				fp = fopen("3.dat", "wb");
				input(T, fp);  //����д����ļ�����д���ļ� 
				fclose(fp);
				system("pause");
				break;
			case 7:  //ɾ��ĳ��Ա 
				system("cls");
				Delete_(T);
				system("pause");
				fp = fopen("3.dat", "wb");
				input(T, fp);  //����д����ļ�����д���ļ� 
				fclose(fp);
				break;
			case 8:  //�޸ĳ�Ա��Ϣ 
				system("cls");
				Modify(T);
				system("pause");
				fp = fopen("3.dat", "wb");
				input(T, fp);  //����д����ļ�����д���ļ� 
				fclose(fp);
				break;
			case 9:
				return 0;
		}
	}
}

