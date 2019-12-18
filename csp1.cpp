// INFO BEGIN
//
// User = 201911508559(Ö£ºÃ) 
// Group = C/C++ 
// Problem = ±¨Êý 
// Language = CPP11 
// SubmitTime = 2019-12-15 13:41:41 
//
// INFO END

#include <iostream>
using namespace std;

bool contains_7(int n)
{
    while(n > 0)
    {
        int temp = n % 10;
        n /= 10;
        if(temp == 7)return true;
    }
    return false;
}
int main()
{
    int n;
    cin >> n;
    int i = 1;
    int pos = 0;
    int time = 0;
    int a[4] = {};
    while(time < n)
    {
        if(i % 7 == 0 || contains_7(i))
        {
            a[pos] ++;
            time --;
        }
        i ++;
        pos ++;
        time ++;
        if(pos == 4)pos = 0;
    }
    for(int j = 0;j < 4;j ++)cout << a[j] << endl;
}
