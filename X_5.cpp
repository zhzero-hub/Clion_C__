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
    int sex = 0;//1Ϊ�У�2ΪŮ
    string date;
    string live;
    string death;
    string addition;
    Node *sib = nullptr;
    Node *couple = nullptr;
    Node *fir = nullptr;
};
vector<Node *> family(10);

void Create()
{
    ifstream file("Family.txt");
    while(!file.eof())
    {
        Node *t = new Node [1];
        file >> t->name;
        string temp;
        file >> temp;
        if(temp == "��")t->sex = 1;
        else if(temp == "Ů")t->sex = 2;
        int gen;
        file >> gen;
        file >> temp;
        if(temp.size() == 10)
        {
            string name = temp.substr(0 , 6);
            Node *pos = family[gen];
            string relation = temp.substr(8 , 2);
            if(relation == "��")
            {

            }
            else if(relation == "��")
            {

            }
            else if(relation == "Ů")
            {

            }
            else if(relation == "��")
            {

            }
        }
    }
}

int main()
{

}















