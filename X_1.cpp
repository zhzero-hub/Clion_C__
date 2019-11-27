//
// Created by haoha on 2019/11/27.
//

#include <iostream>
using namespace std;

int main()
{
    int ans = 0;
    int last = -1;
    int jump;
    int time = 1;
    cin >> jump;
    while(jump != 0)
    {
        if(jump == 1)
        {
            ans ++;
            last = 1;
            time = 1;
        }
        else if(jump == 2)
        {
            if(last == 1 || last == -1)
            {
                time = 1;
                ans += 2;
                last = 2;
            }
            else if(last == 2)
            {
                time ++;
                ans += time * 2;
                last = 2;
            }
        }
        cin >> jump;
    }
    cout << ans;
}