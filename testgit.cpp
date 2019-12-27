//
// Created by Z_HAO on 2019/12/27.
//

#include <iostream>
#include <vector>
using namespace std;

int Binary_search(const vector<int> &x , const int &t , int l , int r)
{
    if(l == r)
    {
        return l;
    }
    int mid = (l + r) / 2;
    int ret = 0;
    if(t < x[mid])
    {
        ret = Binary_search(x , t , l , mid);
    }
    else if(t > x[mid])
    {
        ret = Binary_search(x , t , mid + 1, r);
    }
    else if(t == x[mid])
    {
        return mid;
    }
    return ret;
}

int main()
{
    vector<int> a;
    for(int i = 0;i < 10;i ++)a.push_back(i);
    auto it = a.erase(a.begin());
    int t = *it;
    a.erase(a.begin());
    cout << t;
}