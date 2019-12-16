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
};
vector<Node> family;

void Create()
{
    Node* temp = new Node [1];
    cin >> temp->name;
    cout << temp->name;
}

int main()
{
    Create();
}