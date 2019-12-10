//
// Created by Z_HAO on 2019/12/10.
//

#include <iostream>
using namespace std;

void qsort(int a[] , int p , int q)
{
    int mid = a[(p + q) / 2];
    int l = p , r = q;
    while(l <= r)
    {
        while(a[l] < mid)l ++;
        while(a[r] > mid)r --;
        if(l <= r)
        {
            int t = a[l];
            a[l] = a[r];
            a[r] = t;
            l ++;
            r --;
        }
    }
    if(l < q)qsort(a , l , q);
    if(r > p)qsort(a , p , r);
}

int main()
{
    int a[] = {1,32,13,15,4,56,1,321,5,153,4,56,1123,5,64,654,6,546,84,68,4,1,34,5,453,4,354,3,135,3,54,351,2,13};
    int size = sizeof(a) / sizeof(a[0]);
    qsort(a , 0 , size - 1);
    for(const auto &x: a)cout << x << ' ';
}