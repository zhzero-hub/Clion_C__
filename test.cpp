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
    int sex;
    int generation;
    string place;
    string date;
    string live;
    string culture;
    string addition;
    Node *sib;
    Node *couple;
    Node *fir;
};
vector<Node> family;

void Create()
{
    Node temp;
    cin >> temp.name;
    family.push_back(temp);
}

int main()
{
    string temp = "ÀîÔÆ·å³¤×Ó";
    cout << temp << endl;
}