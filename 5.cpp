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
    int time = 0;//time表示出现次数
    char alphabet = '\0';//alphabet表示对应的字母
    string str = "";//str表示对应的编码
public:
    Tree *l = nullptr;
    Tree *r = nullptr;//二叉树左右孩子节点
    Tree(){alphabet = '\0';time = 0;str = "";l = r = nullptr;};//默认构造函数
    int& Get_time(){return time;};//返回出现次数的引用，获取的同时可以进行更改
    void Set_alphabet(const char &letter){alphabet = letter;l = r = nullptr;};//设置alphabet
    friend bool operator>(const Tree &a , const Tree &b){return a.alphabet > b.alphabet;};//重载大于号，比较两个节点的大小就是比较两个字母的ASCII码
    struct cmp{bool operator()(const Tree *a , const Tree *b){ return  a->time > b->time;}};//结构体重载()，用于比较出现次数，用于排序
    friend bool operator<(const Tree &a , const Tree &b){return a.time < b.time;};
    friend Tree* Insert(Tree *p , Tree *q);//将两个节点作为左右孩子，新建一个节点作为它们的父亲
    static void Code(Tree *t , const string& str , unordered_map<char , string> &code);//用于编码
    void Show_ans();//显示编码结果
    friend void Decoding(Tree *base);//根据Huffman树译码
};

Tree* Insert(Tree *p , Tree *q) {
    Tree* base = (Tree *)malloc(sizeof(Tree));
    base->l = p;
    base->r = q;
    base->time = p->time + q->time;
    return base;
}

void Tree::Code(Tree *t , const string& str , unordered_map<char , string> &code)//后序遍历Huffman树，将对应的编码结果存入节点中
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
        t->str = str;//设置编码
        code.insert(make_pair(t->alphabet , str));//当前字符alphabet和编码str建立映射关系F(alphabet)=str放入集合中
    }
}

void Tree::Show_ans() {//层序遍历二叉树，找到所有叶节点
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
            ans.insert(*temp);//插入的同时会进行排序，插入的时间复杂度为O(logn)
        }
    }
    for(const auto &temp: ans)
        cout << temp.alphabet << "出现的次数为: " << temp.time << " 相应的编码为: " << temp.str << endl;
}

void Coding(const unordered_map<char , string> &code)//根据映射关系对文本进行编码
{
    ifstream file_in("Huffman.txt");
    if(file_in.fail())
    {
        cout << "文件打开失败!";
        exit(0);
    }
    ofstream file_out("Huffman_code.txt");//将编码的结果输出到文本文件中
    while(!file_in.eof())
    {
        char ch = file_in.get();
        if((ch >= 'a' && ch <= 'z') || ch == '0' || ch == '1')
        {
            string temp = code.find(ch)->second;
            file_out << temp;
        }
        else file_out << ch;//不是小写字符的直接跳过
    }
    file_in.close();
    file_out.close();
}

void Decoding(Tree *base)
{
    ifstream file("Huffman_code.txt");//译码
    if(file.fail())
    {
        cout << "文件打开失败!";
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
            if(ch == '0')p = p->l;//如果为0向左走
            else if(ch == '1')p = p->r;//为1向右走
            if(p->l == nullptr && p->r == nullptr)//走到叶节点
            {
                cout << p->alphabet;//输出对应的字符
                p = base;
                break;
            }
            ch = file.get();
        }
    }
}

int main()
{
    priority_queue<Tree * , vector<Tree *> , Tree::cmp> ans;//优先队列
    unordered_map<char , string> code;//映射关系的集合
    ifstream file("Huffman.txt");
    if(file.fail())
    {
        cout << "文件打开失败!";
        exit(0);
    }
    Tree temp[28];//前26个节点对应的就是26个字符的顺序
    for(int i = 0;i < 26;i ++)temp[i].Set_alphabet( i + 'a');
    temp[26].Set_alphabet('0');
    temp[27].Set_alphabet('1');
    while(!file.eof())//统计文章字符出现的次数
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
        if(x.Get_time() > 0)ans.push(&x);//所有出现过的字符进行编码
    }
    file.close();
    while (ans.size() > 1)//最后剩下的就是根节点
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