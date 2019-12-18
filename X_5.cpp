//
// Created by Z_HAO on 2019/12/10.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Person
{
    string name;
    int sex;
    string born_place;
    string born_date;
    string place;
    string culture;
    string addition;
};

struct Node
{
    Person per;
    Node *l = nullptr;
    Node *r = nullptr;
};

void Create()
{
    ifstream file("Family.txt");

}

int main()
{











}