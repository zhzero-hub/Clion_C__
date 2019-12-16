#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int main()
{
    set<int> a;
    unordered_set<int> b;
    for(int i = 1;i <= 10;i ++)
    {
        a.insert(10 - i);
        b.insert(10 - i);
    }
}