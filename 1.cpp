#include<iostream>
#include<cstring>
#include<vector>
#include<iterator>
#include<fstream>
#include<algorithm>
using namespace std;

typedef struct student
{
    char name[20]{};//姓名
    char number[20]{};//学号
    int score = 0;//成绩
    struct student *next = nullptr;//下一个学生
    struct student *pre = nullptr;//上一个学生
    student(){next = pre = nullptr;};//构造函数
    student(char name[] , int score , char num[]){strcpy(name , name);strcpy(number , num);score = score;pre = next = nullptr;};//重载构造函数
    friend istream &operator>>(istream &in , student &t){in >> t.name >> t.score >> t.number;return in;};
}ST;

int menu_select();



int menu_select()
{
    char i;
    do{
        system("cls");
        printf("1.创建纪录（从文件读入）\n");
        printf("2.显示所有记录\n");
        printf("3.插入一条记录\n");
        printf("4.删除一条记录\n");
        printf("5.输入补考成绩\n");
        printf("6.查询\n");
        printf("0.退出\n");
        printf("请输入选择序号(0-6):");
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
        cout << "文件不存在! ";
        exit(0);
    }
    istream_iterator<student> it(file) , eof;
    vector<student> vec(it , eof);//读入所有学生信息到vec
    sort(vec.begin() , vec.end() , compare);//对所有学生信息排序
    student *p = a;
    student *q = b;
    for(auto x: vec)
    {
        auto *temp = (student *)malloc(sizeof(student));//新建一个学生节点
        strcpy(temp->name , x.name);
        strcpy(temp->number , x.number);
        temp->score = x.score;
        if(x.score >= 60)//分为及格和不及格两个链表插入
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
    p->next = q->next = nullptr;//最后将尾节点置空
}

student *Find(student *p , char name[])//从p节点开始寻找名为name的学生节点
{
    if(p == nullptr)
    {
        return nullptr;
    }
    student *q = p;
    while(q != nullptr && strcmp(q->name , name) < 0)q = q->next;
    return q;
}

student *Find(student *p , char num[] , bool &check)//从p节点开始寻找学号为num的学生节点
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

void Show(student *p)//输出学生信息
{
    cout << "姓名: " << p->name << endl;
    cout << "学号: " << p->number << endl;
    cout << "成绩: " << p->score << endl;
    cout << "---------------------------" << endl;
    cout << endl;
}

bool Check(const char num[] , int size)//检查学号信息
{
    if(size != 9)return false;//学号不是9位错误
    for(int i = 0;i < size;i ++)
    {
        if(num[i] >= '0' && num[i] <= '9')continue;
        else return false;//含有不是数字的错误
    }
    return true;
}

void Insert(student *a , student *b)
{
    char name[20] , num[20];
    int score;
    bool check = false;
    cout << "请输入学生姓名: ";
    cin >> name;
    cout << "请输入学生学号: ";
    cin >> num;
    while(true)//检查学号
    {
        int size = strlen(num);
        check = Check(num , size);
        if(check)break;
        else
        {
            cout << "学号输入有误, 请重新输入: ";
            cin >> num;
        }
    }
    cout << "请输入学生成绩: ";
    cin >> score;
    while(score > 100 || score < 0)//检查成绩
    {
        cout << "成绩输入有误, 请重新输入: ";
        cin >> score;
    }
    student *temp = Find(a->next , num , check);//查看这个学生是不是已经存在
    if(temp != nullptr)
    {
        cout << "该学生已存在! " << endl;
        Show(temp);
        return;
    }
    else//不存在就新建节点插入
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
            cout << "插入成功!" << endl;
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
            cout << "插入成功!" << endl;
            return;
        }
    }
}

void Query(student *a , student *b)
{
    char name[20];
    int count = 0;
    cout << "请输入查询学生的姓名: ";
    cin >> name;
    student *p = Find(a->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//如果存在多个姓名相同的学生，那么他们在链表中的位置应该是相邻的
    {
        count ++;
        cout << "第" << count << "位学生的信息为: " << endl;
        Show(p);
        p = Find(p->next , name);
    }
    p = Find(b->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//同理
    {
        count ++;
        cout << "第" << count << "位学生的信息为: " << endl;
        Show(p);
        p = Find(p->next , name);
    }
}

void Del(student *a , student *b)
{
    char name[20];
    int count = 0;
    vector<student *> vec;
    cout << "请输入查询学生的姓名: ";
    cin >> name;
    student *p = Find(a->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//同Query函数，先找到所有符合条件的学生
    {
        count ++;
        cout << "第" << count << "位学生的信息为: " << endl;
        Show(p);
        vec.push_back(p);//加入预删除的数组中
        p = Find(p->next , name);
    }
    p = Find(b->next , name);
    while(p != nullptr && strcmp(p->name , name) == 0)//同上
    {
        count ++;
        cout << "第" << count << "位学生的信息为: " << endl;
        Show(p);//每找到一个学生，就输出他的信息，然后将其节点加入数组中
        vec.push_back(p);
        p = Find(p->next , name);
    }
    for(int i = 0;i < count;i ++)//一个一个确认
    {
        int choice;
        cout << "是否删除第" << i + 1 << "位学生? 输入1确认, 输入0取消: ";
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
            cout << "删除成功! " << endl;
        }
    }
}

void Show_all(student *a , student *b)
{
    int count = 0;
    student *p = a->next;
    cout << "及格名单: " << endl;
    cout << endl;
    while(p != nullptr)
    {
        Show(p);
        count ++;
        p = p->next;
        if(count == 5)//每输出五个学生的信息就暂停一下
        {
            system("pause");
            count = 0;
        }
    }
    cout << "不及格名单: " << endl;
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
    cout << "显示完成!" << endl;
}

void Retest(student *a , student *b)
{
    char name[20] , num[20];
    int score;
    bool check = true;
    cout << "请输入补考学生姓名: ";
    cin >> name;
    cout << "请输入学生学号: ";
    cin >> num;
    while(true)
    {
        int size = strlen(num);
        check = Check(num , size);
        if(check)break;
        else
        {
            cout << "学号输入有误, 请重新输入: ";
            cin >> num;
        }
    }
    student *pos = Find(a->next , num , check);
    if(!check)
    {
        cout << "该生已及格, 不满足补考条件! " << endl;
        cout << "该生信息为: " << endl;
        Show(pos);
        return;
    }
    cout << "请输入补考学生的成绩: ";
    cin >> score;
    while(score > 100 || score < 0)
    {
        cout << "成绩输入有误, 请重新输入: ";
        cin >> score;
    }
    pos = Find(b->next , num , check);
    if(check)
    {
        cout << "未查询到该生! " << endl;
        return;
    }
    else
    {
        if(score >= pos->score)
        {
            pos->score = score;
            if(score >= 60)//补考及格
            {
                student *temp_r = pos->next;//将这个节点的前后两个节点连起来
                student *temp_l = pos->pre;
                temp_l->next = temp_r;
                if(temp_r != nullptr)
                {
                    temp_r->pre = temp_l;
                }
                student *p = Find(a->next , name);//将它插入到及格链表中
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
            cout << "修改完成! " << endl;
            return;
        }
        else
        {
            cout << "该生补考成绩未超过原成绩, 成绩不做修改! " << endl;
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
                printf("调用创建链表函数\n");
                Create(A , B);
                system("pause");
                break;
            case 2:
                printf("调用显示函数\n");
                Show_all(A , B);
                system("pause");
                break;
            case 3:
                printf("调用插入函数\n");
                Insert(A , B);
                system("pause");
                break;
            case 4:
                printf("调用删除函数 :\n");
                Del(A , B);
                system("pause");
                break;
            case 5:
                printf("调用输入补考成绩函数:\n");
                Retest(A , B);
                system("pause");
                break;
            case 6:
                printf("调用查找函数 :\n");
                Query(A , B);
                system("pause");
                break;
            case 0:
                printf("再见\n");
                system("pause");
                exit(0);

        }
        system("cls");
    }
}
