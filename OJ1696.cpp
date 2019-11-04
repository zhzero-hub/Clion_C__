//
// Created by haoha on 2019/11/3.
//

#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    stack<char> str;
    stack<double> ans;
    char ch = getchar();
    while(ch != '\n')
    {
        if(ch == ' ')
        {
            ch = getchar();
            continue;
        }
        if(ch < '0' || ch > '9')
        {
            while(!str.empty() && ans.size() > 1)
            {
                char sh = str.top();
                str.pop();
                double b = ans.top();
                ans.pop();
                double a = ans.top();
                ans.pop();
                double c = 0;
                if(sh == '+')c = a + b;
                else if(sh == '-')c = a - b;
                else if(sh == '*')c = a * b;
                else if(sh == '/')c = a / b;
                ans.push(c);
            }
            str.push(ch);
        }
        else
        {
            string temp;
            while(ch != ' ' && ch != '\n')
            {
                temp += ch;
                ch = getchar();
            }
            double t = atof(temp.c_str());
            ans.push(t);
        }
        if(ch != '\n')ch = getchar();
    }
    while(ans.size() > 1)
    {
        char sh = str.top();
        str.pop();
        double b = ans.top();
        ans.pop();
        double a = ans.top();
        ans.pop();
        double c = 0;
        if(sh == '+')c = a + b;
        else if(sh == '-')c = a - b;
        else if(sh == '*')c = a * b;
        else if(sh == '/')c = a / b;
        ans.push(c);
    }
    printf("%.6f" , ans.top());
    return 0;
}