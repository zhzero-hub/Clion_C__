#include<iostream>
#include <cstdlib>
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

int Initiate(CSNode *&T, FILE *fp)
{
    int n , i;
    for(;;)
    {
        CSNode *p = (CSNode *)malloc(sizeof(CSNode));
        CSNode *q = nullptr;
        cout << i + 1 << endl;
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
        int choose;
        cout << "�Ƿ�ȷ��д��? ";
        cin >> choose;
        if(choose == 1)
        {
            fwrite(&p->data, sizeof(Node), 1, fp);
            if(q)fwrite(&q->data, sizeof(Node), 1, fp);
            cout << "д��ɹ��� " << endl;
        }
        else{
        }
        cout << "�Ƿ����? ";
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