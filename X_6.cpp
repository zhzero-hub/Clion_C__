//
// Created by Z_HAO on 2019/12/23.
//

#include <iostream>
using namespace std;

void qsort(int a[] , int p , int q)
{
    int l = p , r = q , mid = a[(l + r) / 2];
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
    int a[1000010] = {};//存储所有的魔法优惠券
    int price[1000010] = {};//存储所有的商品价格
    int m , n;//m类商品，n类优惠券
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        cin >> a[i];//读取所有优惠券
    }
    cin >> m;
    for(int i = 0;i < m;i ++)
    {
        cin >> price[i];//读取所有商品价格
    }
    int size = m;
    if(n < m)size = n;//size表示m和n中的较小值
    qsort(a , 0 , n - 1);//对优惠券面值进行排序
    qsort(price , 0 , m - 1);//对商品价格进行排序
    int ans = 0;//最终结果
    int temp = 0;//单个商品和优惠券的收益
    int i = 0;//数组指针
    while(a[0] < 0 && price[0] < 0 && temp >= 0)//如果一开始都小于0，那么数组中下表越小的相乘就越大，直到优惠券全部用完或者商品全部被买完或者同时为正
    {
        ans += temp;
        temp = a[i] * price[i];
        i ++;
        if(i >= size)//某一类被用完或买完
        {
            ans += temp;
            cout << ans << endl;
            return 0;
        }
    }
    temp = 0;//出现上述情况，重新置数
    i = n - 1;
    int j = m - 1;//对于正的面额，要从每一个数组的最后一个元素开始相乘相加才最大
    while(temp >= 0)
    {
        ans += temp;
        temp = a[i] * price[j];
        i --;
        j --;
        if(i < 0 || j < 0)//某一类被用完或买完
        {
            ans += temp;
            break;
        }
    }
    cout << ans << endl;//在这里输出是为了防止出现一类全为正，一类全为负的情况，这样最佳方案是什么都不买
}