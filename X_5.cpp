//
// Created by haoha on 2019/12/16.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

struct Node
{
    string name;
    int sex = 0;//1为男，2为女
    string date;
    string live;
    string death;
    string addition;
    Node *sib = nullptr;
    Node *couple = nullptr;
    Node *fir = nullptr;
};
vector<Node *> family(10);

Node *find(Node *x , const string &t)
{
    if(x == nullptr)
    {
        return nullptr;
    }
    if(x->name == t)
    {
        return x;
    }
    else if(x->couple->name == t)
    {
        return x->couple;
    }
    Node *p = find(x->sib , t);
    Node *q = find(x->fir , t);
    if(p != nullptr)return p;
    else if(q != nullptr)return q;
    else return nullptr;
}

void Create()
{
    ifstream file("Family.txt");
    while(!file.eof())
    {
        Node *t = new Node [1];
        file >> t->name;
        string temp;
        file >> temp;
        if(temp == "男")t->sex = 1;
        else if(temp == "女")t->sex = 2;
        int gen;
        file >> gen;
        file >> temp;
        if(temp.size() == 10)
        {
            string name = temp.substr(0 , 6);
            Node *pos = find(family[gen] , name);
            string relation = temp.substr(8 , 2);
            if(relation == "妻")
            {
                pos->couple = t;
            }
            else if(relation == "子")
            {
                pos->fir = t;
            }
            else if(relation == "女")
            {
                pos->fir = t;
            }
            else if(relation == "婿")
            {
                
            }
        }
    }
}

int main()
{

}















