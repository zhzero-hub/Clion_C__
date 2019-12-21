#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

struct Node
{
	char name[10];//����
	char birth[12];//��������
	int marriage;//���
	Node *couple = nullptr;
	char address[50];//��ַ
	int health;//�Ƿ���
	char death[12];//��������
};

struct CSNode//�����ֵ���
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
			Create(T->fir , fp);//�ݹ��ȡ��Ϣ
			Create(T->sib , fp);
		}
	}
}

int Initiate(CSNode * &T, FILE *fp)
{
	int n , i;
	CSNode *p = (CSNode *)malloc(sizeof(CSNode));
	CSNode *q = nullptr;
	cout << "������n:";
	cin >> n;
	for(i = 0; i < n; i++)
    {
		cout << i + 1;
		cout << "����: ";
		cin >> p->data.name;
		cout << "��������: ";
		cin >> p->data.birth;
		cout << "���: ";
		cin >> p->data.marriage;
		if(p->data.marriage) {
            q = (CSNode *)malloc(sizeof(CSNode));
            cout << i + 1;
            cout << "����: ";
            cin >> q->data.name;
            cout << "��������: ";
            cin >> q->data.birth;
            q->data.marriage = 1;
            cout << "��ַ: ";
            cin >> q->data.address;
            cout << "���ڷ�: ";
            cin >> q->data.health;
            cout << "��������: ";
            cin >> q->data.death;
            p->data.couple = &q->data;
            q->data.couple = &p->data;
            system("cls");
		}
		cout << "��ַ: ";
		cin >> p->data.address;
		cout << "���ڷ�: ";
		cin >> p->data.health;
		cout << "��������: ";
		cin >> p->data.death;
		system("cls");
		fwrite(&p->data, sizeof(Node), 1, fp);
        if(q)fwrite(&q->data, sizeof(Node), 1, fp);
	}
	return 1;
}

void Print(Node *T)  //�����Ա����Ϣ
{
	cout << endl;
    cout << "������" << T->name << endl;
	cout << "�������ڣ�" << T->birth << endl;
	cout << "���";
	if(T->marriage){
        cout << "�ѻ�" << endl;
        cout << "��ż��ϢΪ: " << endl;
        Print(T->couple);
	}
	else cout << "δ��" << endl;
	cout << "��ַ��" << T->address << endl;
	cout << "���ڷ�";
	if(T->health)
        cout << "��" << endl;
	else
    {
		cout << "��";
		cout << "�������ڣ�" << T->death << endl;
	} 
} 

void Show_gen(CSNode * T, int m)  //�����n���˵�������Ϣ 
{//��Ҫ��ͼ�λ�����
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

void Show_n(CSNode * T, int m, int &j, int N2)  //�����n���˵�������Ϣ 
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

void Pre(CSNode * T)  //��������е������� 
{
	if(T)
    {
		all ++;
		Pre(T->fir);
		Pre(T->sib);
	}
}

void Show(CSNode * T)  //��ʾ���� 
{
	int j = 0, num = 0;
	int N2 = 1;
	all = 0;
	Pre(T);
	for(int i = 0; i < 10 && num < all; i++, N2++)
    {
		cout << "��" << i + 1 << "��: ";
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

void input(CSNode * T, FILE *fp) //���޸ĺ����Ϣ���´����ļ�
{
	Node p{};   //���
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
	cout << "1.��ͼ�η�ʽ��ʾ����" << endl;
	cout << "2.��ʾ��n �������˵���Ϣ" << endl;
	cout << "3.����������ѯ" << endl;
	cout << "4.���ճ������ڲ�ѯ" << endl;
	cout << "5.ȷ�����˹�ϵ" << endl;
	cout << "6.ĳ��Ա��Ӻ���" << endl;
	cout << "7.ɾ��ĳ��Ա" << endl;
	cout << "8.�޸ĳ�Ա��Ϣ" << endl;
	cout << "9.�˳�" << endl;
    cout << "����ѡ��: ";
	cin >> choose;
	while(choose < 1 || choose > 9)
    {
		cout << "���벻�Ϸ���";
		cin >> choose;
	}
	return choose;
}

void PreOrder(CSNode * T, CSNode * &p, char na[])   //�����������������������
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

void Find_Parent(CSNode *T, CSNode *&p, CSNode *&f, char na[])   //�Ҹó�Ա�ĸ���
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

void Del(CSNode * &p)  //ɾ��p������������ 
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

void Delete(CSNode * &T)   //ɾ����Ա������
{
	CSNode *p, *f, *c;
	p = f = nullptr;
	char na[10];
	cout << "����: ";
	cin >> na;
	PreOrder(T, p, na);
	if(!p)
    {
		cout << "δ�ҵ��ó�Ա!" << endl;
		return;
	}
	else
    {
		Find_Parent(T, p, f, na);   //fΪ��ɾ������˫�׽�� 
		if(f == nullptr)//T�Ǹ��ڵ�
            T = nullptr;//ɾ�����Ǹ����
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

int Query_Birth(CSNode * T)  //���ճ������ڲ�ѯ 
{
	CSNode * p;
	p = nullptr;
	char bir[12];
	cout << "����: ";
	cin >> bir;
	PreOrder_Birth(T, p, bir);
	if(!p)
    {
		cout<<"δ�ҵ��ó�Ա��" << endl;
		return 0;
	}
	else
		Print(&p->data);
}

void Query_Name(CSNode * T)  //����������ѯ
{
	CSNode *p, *f, *c;
	int flag;
	p = f = nullptr;
	char na[10];
	cout << "������";
	cin >> na;
	PreOrder(T, p, na); //�ݹ����
	if(p == nullptr)
    {
		cout << "δ�ҵ��ó�Ա!";
		return;
	} 
	else {
	    cout << "������Ϣ: " <<endl;
		Print(&p->data);  //����ó�Ա����Ϣ
		Find_Parent(T, p, f, na);
		cout << "���׵���Ϣ��";
		if(f != nullptr)
			Print(&f->data);
		else cout << "�ޣ�" << endl;
		cout << "������Ϣ: " << endl;
		c = p->fir;
		flag = 0;
		while(c)
        {
			flag = 1;
			Print(&c->data);
			c = c->sib;
		}
		if(!flag) 
            cout << "�ޣ�" << endl;
	}
}

void Add_Child(CSNode * &T)  //���һ������
{
	CSNode * f, *child, *p;  //���׽��
	char f_name[10]; 
	cout << "�����븸�׵�������";
	cin >> f_name;
	PreOrder(T, f, f_name);
	if(!f)
    {
		cout << "δ�ҵ��ø��׵���Ϣ!" << endl;
		return;
	}
	else
    {
		cout << "�����뺢�ӵ���Ϣ��";
		child = (CSNode *)malloc(sizeof(CSNode));
		if(!child)
        {
		    exit(0);
        }
		cout << "����: ";
		cin >> child->data.name;
		cout << "��������: ";
		cin >> child->data.birth;
		cout << "��ַ: ";
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

int Modify(CSNode * &T)  //�޸ĳ�Ա����Ϣ 
{
	CSNode *p = nullptr;
	char na[10];
	int choose;
	cout << "������Ҫ�޸ĵĳ�Ա��������";
	cin >> na;
	PreOrder(T, p, na);
	if(p == nullptr)
    {
		cout << "δ�ҵ��ó�Ա��" << endl;
		return 0;
	}
	else
    {
		cout << "1.����" << endl;
		cout << "2.��������" << endl;
		cout << "3.���" << endl;
		cout << "4.��ַ" << endl;
		cout << "5.���ڷ�" << endl;
		cout << "6.��������" << endl;
		cout << "����ѡ��: ";
		cin >> choose;
		while(choose < 1 || choose > 6)
        {
			cout << "���벻�Ϸ���";
			cin >> choose;
		}
		if(choose == 1) {
            cout << "�������µ�����: ";
            cin >> p->data.name;
        }
		else if(choose == 2) {
            cout << "�������µĳ�������: ";
            cin >> p->data.birth;
        }
		else if(choose == 3) {
            cout << "�������µĻ������(0-δ��,1-�ѻ�): ";
            cin >> p->data.marriage;
        }
		else if(choose == 4) {
            cout << "�������µĵ�ַ: ";
            cin >> p->data.address;
        }
		else if(choose == 5) {
            cout << "�������µĽ������(0-����,1-����): ";
            cin >> p->data.health;
            if (!p->data.health) {
                cout << "��������������: ";
                cin >> p->data.death;
            }
        }
		else if(choose == 6) {
            cout << "�������µ���������: ";
            cin >> p->data.death;
        }
    }
	cout<<"�޸ĺ�ó�Ա����Ϣ�� " << endl;
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
	cout << "�������һ���˵�������";
	cin >> name1;
	cout << "������ڶ����˵�������";
	cin >> name2;
	Find_Parent(T, p1, f1, name1);  //�ҵ����˵ĸ��� 
	Find_Parent(T, p2, f2, name2);
	Find_gen(T, name1, gen1, 1);  //�ж������˵Ĵ��� 
	Find_gen(T, name2, gen2, 1);
	if(f1 == f2) {
        cout << "���ֵ�" << endl;
        return;
    }
	else if(gen1 == gen2) {
        cout << "���ֵ�" << endl;
        return;
	}
	else if(fabs(gen1 - gen2) == 1) {
		if(p1 == f2 || p2 == f1) {
            cout << "����" << endl;
        }
		else {
            cout << "��ֶ" << endl;
        }
		return;
	}
	else if(fabs(gen1 - gen2) == 2) {
		Find_Parent(T, f1, g1, f1->data.name);
		Find_Parent(T, f2, g2, f2->data.name);
		if(g1 == p2 || g2 == p1) 
            cout << "ү��" << endl;
		else 
            cout << "���游" << endl;
		return;
	}
	else if(fabs(gen1 - gen2) == 3) {
        cout << "���游" << endl;
        return;
    }
	else cout << "�����������ڵĹ�ϵ" << endl;
}

int main()
{
	CSNode *T;
	Node p;
	char na[10];
	int choose;
	FILE *fp = fopen("����.dat", "rb");
	Create(T, fp);  //���ļ��ж�ȡ��Ϣ�������Ժ����ֵܱ�ʾ����
	fclose(fp);
	while(true)
    {
		system("cls");
		choose = menu();
        if(choose == 1) {
            //��ͼ�η�ʽ��ʾ����
            system("cls");
            Show(T);
            system("pause");
        }
        else if(choose == 2) {
            //��ʾ��n�������˵���Ϣ
            system("cls");
            cout << "������n: ";
            cin >> N;
            Show_gen(T, 1);
            system("pause");
        }
		else if(choose == 3) {
            //����������ѯ
            system("cls");
            Query_Name(T);
            system("pause");
        }
		else if(choose == 4) {
            //���ճ������ڲ�ѯ
            system("cls");
            Query_Birth(T);
            system("pause");
        }
		else if(choose == 5) {
            //ȷ�����˹�ϵ
            system("cls");
            Relationship(T);
            system("pause");
        }
		else if(choose == 6) {
            //ĳ��Ա��Ӻ���
            system("cls");
            Add_Child(T);
            fp = fopen("3.dat", "wb");
            input(T, fp);  //����д����ļ�����д���ļ�
            fclose(fp);
            system("pause");
        }
		else if(choose == 7) {
            //ɾ��ĳ��Ա
            system("cls");
            Delete(T);
            system("pause");
            fp = fopen("3.dat", "wb");
            input(T, fp);  //����д����ļ�����д���ļ�
            fclose(fp);
        }
		else if(choose == 8) {
            //�޸ĳ�Ա��Ϣ
            system("cls");
            Modify(T);
            system("pause");
            fp = fopen("3.dat", "wb");
            input(T, fp);  //����д����ļ�����д���ļ�
            fclose(fp);
        }
		else {
		    break;
		}
	}
}

