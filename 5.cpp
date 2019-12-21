//
// Created by haoha on 2019/10/14.
//

#include <iostream>
#include <queue>
#include <fstream>
#include <set>
#include <unordered_map>
using namespace std;

class Tree
{
private:
    int time = 0;//time��ʾ���ִ���
    char alphabet = '\0';//alphabet��ʾ��Ӧ����ĸ
    string str = "";//str��ʾ��Ӧ�ı���
public:
    Tree *l = nullptr;
    Tree *r = nullptr;//���������Һ��ӽڵ�
    Tree(){alphabet = '\0';time = 0;str = "";l = r = nullptr;};//Ĭ�Ϲ��캯��
    int& Get_time(){return time;};//���س��ִ��������ã���ȡ��ͬʱ���Խ��и���
    void Set_alphabet(const char &letter){alphabet = letter;l = r = nullptr;};//����alphabet
    friend bool operator>(const Tree &a , const Tree &b){return a.alphabet > b.alphabet;};//���ش��ںţ��Ƚ������ڵ�Ĵ�С���ǱȽ�������ĸ��ASCII��
    struct cmp{bool operator()(const Tree *a , const Tree *b){ return  a->time > b->time;}};//�ṹ������()�����ڱȽϳ��ִ�������������
    friend bool operator<(const Tree &a , const Tree &b){return a.time < b.time;};
    friend Tree* Insert(Tree *p , Tree *q);//�������ڵ���Ϊ���Һ��ӣ��½�һ���ڵ���Ϊ���ǵĸ���
    static void Code(Tree *t , const string& str , unordered_map<char , string> &code);//���ڱ���
    void Show_ans();//��ʾ������
    friend void Decoding(Tree *base);//����Huffman������
};

Tree* Insert(Tree *p , Tree *q) {
    Tree* base = (Tree *)malloc(sizeof(Tree));
    base->l = p;
    base->r = q;
    base->time = p->time + q->time;
    return base;
}

void Tree::Code(Tree *t , const string& str , unordered_map<char , string> &code)//�������Huffman��������Ӧ�ı���������ڵ���
{
    if(t == nullptr)return;
    if(t->l != nullptr)
    {
        string temp_str = str + "0";
        Code(t->l ,  temp_str , code);
    }
    if(t->r != nullptr)
    {
        string temp_str = str + "1";
        Code(t->r , temp_str , code);
    }
    if((t->alphabet >= 'a' && t->alphabet <= 'z') || t->alphabet == '0' || t->alphabet == '1')
    {
        t->str = str;//���ñ���
        code.insert(make_pair(t->alphabet , str));//��ǰ�ַ�alphabet�ͱ���str����ӳ���ϵF(alphabet)=str���뼯����
    }
}

void Tree::Show_ans() {//����������������ҵ�����Ҷ�ڵ�
    queue<Tree*> q;
    set<Tree> ans;
    q.push(this);
    while(!q.empty())
    {
        Tree *temp = q.front();
        q.pop();
        if(temp->l != nullptr)q.push(temp->l);
        if(temp->r != nullptr)q.push(temp->r);
        if((temp->alphabet >= 'a' && temp->alphabet <= 'z') || temp->alphabet == '0' || temp->alphabet == '1')
        {
            ans.insert(*temp);//�����ͬʱ��������򣬲����ʱ�临�Ӷ�ΪO(logn)
        }
    }
    for(const auto &temp: ans)
        cout << temp.alphabet << "���ֵĴ���Ϊ: " << temp.time << " ��Ӧ�ı���Ϊ: " << temp.str << endl;
}

void Coding(const unordered_map<char , string> &code)//����ӳ���ϵ���ı����б���
{
    ifstream file_in("Huffman.txt");
    if(file_in.fail())
    {
        cout << "�ļ���ʧ��!";
        exit(0);
    }
    ofstream file_out("Huffman_code.txt");//������Ľ��������ı��ļ���
    while(!file_in.eof())
    {
        char ch = file_in.get();
        if((ch >= 'a' && ch <= 'z') || ch == '0' || ch == '1')
        {
            string temp = code.find(ch)->second;
            file_out << temp;
        }
        else file_out << ch;//����Сд�ַ���ֱ������
    }
    file_in.close();
    file_out.close();
}

void Decoding(Tree *base)
{
    ifstream file("Huffman_code.txt");//����
    if(file.fail())
    {
        cout << "�ļ���ʧ��!";
        exit(0);
    }
    Tree *p = base;
    while(!file.eof())
    {
        char ch = file.get();
        if(ch < '0' || ch > '1')
        {
            cout << ch;
            continue;
        }
        while(ch == '0' || ch == '1')
        {
            if(ch == '0')p = p->l;//���Ϊ0������
            else if(ch == '1')p = p->r;//Ϊ1������
            if(p->l == nullptr && p->r == nullptr)//�ߵ�Ҷ�ڵ�
            {
                cout << p->alphabet;//�����Ӧ���ַ�
                p = base;
                break;
            }
            ch = file.get();
        }
    }
}

int main()
{
    priority_queue<Tree * , vector<Tree *> , Tree::cmp> ans;//���ȶ���
    unordered_map<char , string> code;//ӳ���ϵ�ļ���
    ifstream file("Huffman.txt");
    if(file.fail())
    {
        cout << "�ļ���ʧ��!";
        exit(0);
    }
    Tree temp[28];//ǰ26���ڵ��Ӧ�ľ���26���ַ���˳��
    for(int i = 0;i < 26;i ++)temp[i].Set_alphabet( i + 'a');
    temp[26].Set_alphabet('0');
    temp[27].Set_alphabet('1');
    while(!file.eof())//ͳ�������ַ����ֵĴ���
    {
        char ch = file.get();
        if(ch == '0')
        {
            ++ temp[26].Get_time();
            continue;
        }
        else if(ch == '1')
        {
            ++ temp[27].Get_time();
            continue;
        }
        int t = ch - 'a';
        if(t >= 0 && t <= 25)++ temp[t].Get_time();
    }
    for(auto& x: temp)
    {
        if(x.Get_time() > 0)ans.push(&x);//���г��ֹ����ַ����б���
    }
    file.close();
    while (ans.size() > 1)//���ʣ�µľ��Ǹ��ڵ�
    {
        Tree* a = ans.top();
        ans.pop();
        Tree* b = ans.top();
        ans.pop();
        Tree* t = Insert(a , b);
        ans.push(t);
    }
    Tree* Ans = ans.top();
    Ans->Code(Ans , "" , code);
    Ans->Show_ans();
    Coding(code);
    Decoding(Ans);
}