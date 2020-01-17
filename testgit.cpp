//
// Created by Z_HAO on 2019/11/27.
//

#include <iostream>
#include <stack>
using namespace std;

int main()
{
    stack<int> a;
    stack<int> b;
    int l , r;
    cin >> l >> r;
    while(l > 0)
    {
        a.push(l);
        l /= 2;
    }
    while(r > 0)
    {
        b.push(r);
        r /= 2;
    }
    int ans = 1;
    while(!a.empty() && !b.empty() && a.top() == b.top())
    {
        ans = a.top();
        a.pop();
        b.pop();
    }
    cout << ans;
    return 0;
}
















