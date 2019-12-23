#include<iostream>
#include <cstdlib>
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

int Initiate(CSNode *&T, FILE *fp)
{
    int n , i;
    for(;;)
    {
        CSNode *p = (CSNode *)malloc(sizeof(CSNode));
        CSNode *q = nullptr;
        cout << i + 1 << endl;
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
        int choose;
        cout << "是否确认写入? ";
        cin >> choose;
        if(choose == 1)
        {
            fwrite(&p->data, sizeof(Node), 1, fp);
            if(q)fwrite(&q->data, sizeof(Node), 1, fp);
            cout << "写入成功！ " << endl;
        }
        else{
        }
        cout << "是否继续? ";
        cin >> choose;
        if(choose == 0)break;
        system("cls");
    }
    return 1;
}

int main()
{
    CSNode *T;
    FILE *fp;
    fp = fopen("database","wb");
    if(!fp)
        exit(0);
    Initiate(T , fp);
    fclose(fp);
}