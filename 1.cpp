#include<iostream>
#include<cstring>
#include<vector>
#include<iterator>
#include<fstream>
#include<algorithm>
using namespace std;

typedef struct student
{
    char name[20]{};//����
    char number[20]{};//ѧ��
    int score = 0;//�ɼ�
    struct student *next = nullptr;//��һ��ѧ��
    struct student *pre = nullptr;//��һ��ѧ��
    student(){next = pre = nullptr;};//���캯��
    student(char name[] , int score , char num[]){strcpy(name , name);strcpy(number , num);score = score;pre = next = nullptr;};//���ع��캯��
    friend istream &operator>>(istream &in , student &t){in >> t.name >> t.score >> t.number;return in;};
}ST;

int menu_select();



int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.������¼�����ļ����룩\n");
        printf("2.��ʾ���м�¼\n");
        printf("3.����һ����¼\n");
        printf("4.ɾ��һ����¼\n");
        printf("5.���벹���ɼ�\n");
        printf("6.��ѯ\n");
        printf("0.�˳�\n");
        printf("������ѡ�����(0-6):");
        cin >> i;
    }while(i<'0' || i>'6');
    return (i - '0');
}

bool compare(student &a , student &b)
{
    if(strcmp(a.name , b.name) == 0)
    {
        return a.number < b.number;
    }
    return strcmp(a.name , b.name) < 0;
}

void Create(student *a , student *b)
{
    ifstream file("01.txt");
    if(file.fail())
    {
        cout << "�ļ�������! ";
        exit(0);
    }
    istream_iterator<student> it(file) , eof;
    vector<student> vec(it , eof);//��������ѧ����Ϣ��vec
    sort(vec.begin() , vec.end() , compare);//������ѧ����Ϣ����
    student *p = a;
    student *q = b;
    for(auto x: vec)
    {
        auto *temp = (student *)malloc(sizeof(student));//�½�һ��ѧ���ڵ�
        strcpy(temp->name , x.name);
        strcpy(temp->number , x.number);
        temp->score = x.score;
        if(x.score >= 60)//��Ϊ����Ͳ����������������
        {
            p->next = temp;
            temp->pre = p;
            p = p->next;
        }
        else
        {
            q->next = temp;
            temp->pre = q;
            q = q->next;
        }
    }
    p->next = q->next = nullptr;//���β�ڵ��ÿ�
}

student *Find(student *p , char name[])//��p�ڵ㿪ʼѰ����Ϊname��ѧ���ڵ�
{
    if(p == nullptr)
    {
        return nullptr;
    }
    student *q = p;
    while(q != nullptr && strcmp(q->name , name) < 0)q = q->next;
    return q;
}

student *Find(student *p , char num[] , bool &check)//��p�ڵ㿪ʼѰ��ѧ��Ϊnum��ѧ���ڵ�
{
    if(p == nullptr)return nullptr;
    student *q = p;
    while(q != nullptr && strcmp(q->number , num) != 0)q = q->next;
    if(q == nullptr)
    {
        check = true;
        return nullptr;
    }
    else
    {
        check = false;
        return q;
    }
}

void Show(student *p)//���ѧ����Ϣ
{
    cout << "����: " << p->name << endl;
    cout << "ѧ��: " << p->number << endl;
    cout << "�ɼ�: " << p->score << endl;
    cout << "---------------------------" << endl;
    cout << endl;
}

bool Check(const char num[] , int size)//���ѧ����Ϣ
{
    if(size != 9)return false;//ѧ�Ų���9λ����
    for(int i = 0;i < size;i ++)
    {
        if(num[i] >= '0' && num[i] <= '9')continue;
        else return false;//���в������ֵĴ���
    }
    return true;
}

void Insert(student *a , student *b)
{
    char name[20] , num[20];
    int score;
    bool check = false;
    cout << "������ѧ������: ";
    cin >> name;
    cout << "������ѧ��ѧ��: ";
    cin >> num;
    while(true)//���ѧ��
    {
        int size = strlen(num);
        check = Check(num , size);
        if(check)break;
        else
        {
            cout << "ѧ����������, ����������: ";
            cin >> num;
        }
    }
    cout << "������ѧ���ɼ�: ";
    cin >> score;
    while(score > 100 || score < 0)//���ɼ�
    {
        cout << "�ɼ���������, ����������: ";
        cin >> score;
    }
    student *temp = Find(a->next , num , check);//�鿴���ѧ���ǲ����Ѿ�����
    if(temp != nullptr)
    {
        cout << "��ѧ���Ѵ���! " << endl;
        Show(temp);
        return;
    }
    else//�����ھ��½��ڵ����
    {
        auto *t = (student *)malloc(sizeof(student));
        strcpy(t->name , name);
        strcpy(t->number , num);
        t->score = score;
        if(score >= 60)
        {
            student *pos = Find(a->next , name);
            if(strcmp(pos->name , name) == 0)
            {
                while(strcmp(num , pos->number) < 0)pos = pos->next;
                if(strcmp(pos->number , num) > 0)
                {
                    student *l = pos->pre;
                    l->next = t;
                    t->pre = l;
                    t->next = pos;
                    pos->pre = t;
                }
                else {
                    student *r = pos->next;
                    r->pre = t;
                    t->next = r;
                    t->pre = pos;
                    pos->next = t;
                }
                return;
            }
            if((strcmp(pos->name , name) > 0))
            {
                student *l = pos->pre;
                l->next = t;
                t->pre = l;
                t->next = pos;
                pos->pre = t;
            }
            else
            {
                pos->next = t;
                t->pre = pos;
                t->next = nullptr;
            }
            cout << "����ɹ�!" << endl;
            return;
        }
        else
        {
            student *pos = Find(b->next , name);
            if((strcmp(pos->name , name) > 0))
            {
                student *l = pos->pre;
                l->next = t;
                t->pre = l;
                t->next = pos;
                pos->pre = t;
            }
            else
            {
                pos->next = t;
                t->pre = pos;
                t->next = nullptr;
            }
            cout << "����ɹ�!" << endl;
            return;
        }
    }
}

void Query(student *a , student *b)
{
    char name[20];
    int count = 0;
    cout << "�������ѯѧ��������: ";
    cin >> name;
    student *p = Find(a->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//������ڶ��������ͬ��ѧ������ô�����������е�λ��Ӧ�������ڵ�
    {
        count ++;
        cout << "��" << count << "λѧ������ϢΪ: " << endl;
        Show(p);
        p = Find(p->next , name);
    }
    p = Find(b->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//ͬ��
    {
        count ++;
        cout << "��" << count << "λѧ������ϢΪ: " << endl;
        Show(p);
        p = Find(p->next , name);
    }
}

void Del(student *a , student *b)
{
    char name[20];
    int count = 0;
    vector<student *> vec;
    cout << "�������ѯѧ��������: ";
    cin >> name;
    student *p = Find(a->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//ͬQuery���������ҵ����з���������ѧ��
    {
        count ++;
        cout << "��" << count << "λѧ������ϢΪ: " << endl;
        Show(p);
        vec.push_back(p);//����Ԥɾ����������
        p = Find(p->next , name);
    }
    p = Find(b->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//ͬ��
    {
        count ++;
        cout << "��" << count << "λѧ������ϢΪ: " << endl;
        Show(p);//ÿ�ҵ�һ��ѧ���������������Ϣ��Ȼ����ڵ����������
        vec.push_back(p);
        p = Find(p->next , name);
    }
    for(int i = 0;i < count;i ++)//һ��һ��ȷ��
    {
        int choice;
        cout << "�Ƿ�ɾ����" << i + 1 << "λѧ��? ����1ȷ��, ����0ȡ��: ";
        cin >> choice;
        if(choice == 1)
        {
            student *temp = vec[i];
            student *l = temp->pre;
            if(temp->next == nullptr)
            {
                free(temp);
                l->next = nullptr;
            }
            else
            {
                student *r = temp->next;
                free(temp);
                l->next = r;
                r->pre = l;
            }
            cout << "ɾ���ɹ�! " << endl;
        }
    }
}

void Show_all(student *a , student *b)
{
    int count = 0;
    student *p = a->next;
    cout << "��������: " << endl;
    cout << endl;
    while(p != nullptr)
    {
        Show(p);
        count ++;
        p = p->next;
        if(count == 5)//ÿ������ѧ������Ϣ����ͣһ��
        {
            system("pause");
            count = 0;
        }
    }
    cout << "����������: " << endl;
    cout << endl;
    student *q = b->next;
    while(q != nullptr)
    {
        Show(q);
        count ++;
        q = q->next;
        if(count == 5)
        {
            system("pause");
            count = 0;
        }
    }
    cout << "��ʾ���!" << endl;
}

void Retest(student *a , student *b)
{
    char name[20] , num[20];
    int score;
    bool check = true;
    cout << "�����벹��ѧ������: ";
    cin >> name;
    cout << "������ѧ��ѧ��: ";
    cin >> num;
    while(true)
    {
        int size = strlen(num);
        check = Check(num , size);
        if(check)break;
        else
        {
            cout << "ѧ����������, ����������: ";
            cin >> num;
        }
    }
    student *pos = Find(a->next , num , check);
    if(!check)
    {
        cout << "�����Ѽ���, �����㲹������! " << endl;
        cout << "������ϢΪ: " << endl;
        Show(pos);
        return;
    }
    cout << "�����벹��ѧ���ĳɼ�: ";
    cin >> score;
    while(score > 100 || score < 0)
    {
        cout << "�ɼ���������, ����������: ";
        cin >> score;
    }
    pos = Find(b->next , num , check);
    if(check)
    {
        cout << "δ��ѯ������! " << endl;
        return;
    }
    else
    {
        if(score >= pos->score)
        {
            pos->score = score;
            if(score >= 60)//��������
            {
                student *temp_r = pos->next;//������ڵ��ǰ�������ڵ�������
                student *temp_l = pos->pre;
                temp_l->next = temp_r;
                if(temp_r != nullptr)
                {
                    temp_r->pre = temp_l;
                }
                student *p = Find(a->next , name);//�������뵽����������
                if((strcmp(p->name , name) > 0))
                {
                    student *l = p->pre;
                    l->next = pos;
                    pos->pre = l;
                    pos->next = p;
                    p->pre = pos;
                }
                else
                {
                    p->next = pos;
                    pos->pre = p;
                    pos->next = nullptr;
                }
            }
            cout << "�޸����! " << endl;
            return;
        }
        else
        {
            cout << "���������ɼ�δ����ԭ�ɼ�, �ɼ������޸�! " << endl;
            return;
        }
    }
}

int main()
{
    ST *A,*B;
    A=(ST *)malloc(sizeof(ST));
    B=(ST *)malloc(sizeof(ST));
    A->next=B->next=nullptr;
    for(;;)
    {
        switch(menu_select())
        {
            case 1:
                printf("���ô���������\n");
                Create(A , B);
                system("pause");
                break;
            case 2:
                printf("������ʾ����\n");
                Show_all(A , B);
                system("pause");
                break;
            case 3:
                printf("���ò��뺯��\n");
                Insert(A , B);
                system("pause");
                break;
            case 4:
                printf("����ɾ������ :\n");
                Del(A , B);
                system("pause");
                break;
            case 5:
                printf("�������벹���ɼ�����:\n");
                Retest(A , B);
                system("pause");
                break;
            case 6:
                printf("���ò��Һ��� :\n");
                Query(A , B);
                system("pause");
                break;
            case 0:
                printf("�ټ�\n");
                system("pause");
                exit(0);

        }
        system("cls");
    }
}
