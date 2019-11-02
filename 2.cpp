#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

bool res(string &name , stack<char> &p , queue<string> &q)
{
    for(auto x = name.begin();x < name.end();x ++)
    {
        if((*x >= '0' && *x <= '9') || *x == '.')
        {
            string num;
            int time = 0;//time表示小数点出现的次数，因为一个数字不能包含两个小数点
            while((*x >= '0' && *x <= '9') || *x == '.')
            {
                num += *x;
                x ++;
                if(*x == '.')
                {
                    if(time == 1)return false;
                    time ++;
                    num += *x;
                    x ++;
                }
            }
            x --;
            q.push(num);
        }
        else
        {
            if(*x == '(')p.push(*x);
            else if(*x == ')')
            {
                char ch = p.top();
                p.pop();
                while(ch != '(')
                {
                    string temp(1 , ch);
                    q.push(temp);
                    if(p.empty())return false;
                    ch = p.top();
                    p.pop();
                }
            }
            else if(*x == '*' || *x == '/')p.push(*x);
            else if(*x == '+' || *x == '-')
            {
                if(p.empty())
                {
                    p.push(*x);
                    continue;
                }
                char ch = p.top();
                while(ch != '(')
                {
                    p.pop();
                    string temp(1 , ch);
                    q.push(temp);
                    if(p.empty())break;
                    else
                    {
                        ch = p.top();
                    }   
                }
                p.push(*x);
            }
            else return false;
        }
    }
    while(!p.empty())
    {
        char ch = p.top();
        p.pop();
        string temp(1 , ch);
        q.push(temp);
    }
    return true;
}

double Cal(double &a , double &b , bool &ans , string &sig)
{
    if(sig == "+")return a + b;
    else if(sig == "-")return a - b;
    else if(sig == "*")return a * b;
    else if(sig == "/")
    {
        if(b == 0)ans = false;
        return a / b;
    }
}

double res_double(string &t)
{
    double ans = 0;
    auto pos = t.find('.');
    if(pos == -1)
    {
        for(auto x: t)
        {
            int temp = x - '0';
            ans *= 10;
            ans += temp;
        }
    }
    else
    {
        int size = t.size();
        for(int p = 0;p < pos;p ++)
        {
            double temp = t[p] - '0';
            ans *= 10;
            ans += temp;
        }
        for(int p = t.size() - 1;p > pos;p --)
        {
            double temp = t[p] - '0';
            temp /= 10;
            ans += temp;
        }
    }
    return ans;
}

bool Ans(queue<string> &q , double &ans)
{
    stack<double> p;
    while(!q.empty())
    {
        string x = q.front();
        q.pop();
        if(x == "+" || x == "-" || x == "*" || x == "/")
        {
            if(p.empty())return false;
            double b = p.top();
            p.pop();
            if(p.empty())return false;
            double a = p.top();
            p.pop();
            bool check = true;
            double c = Cal(a , b , check , x);
            if(check)p.push(c);
            else return false;
        }
        else
        {
            double temp = res_double(x);
            p.push(temp);
        }
    }
    if(p.size() == 1)ans = p.top();
    else return false;
    return true;
}

int main()
{
    string name;
    double ans = 0;
    cout << "请输入表达式: ";
    getline(cin , name);
    while(name != "#")
    {
        stack<char> p;
        queue<string> q;
        if(res(name , p , q))
        {
            queue<string> out(q);
            cout << "后缀表达式为: ";
            while(!out.empty())
            {
                cout << out.front() << ' ';
                out.pop();
            }
            cout << endl;
            bool check = Ans(q , ans);
            if(check)
            {
                printf("结果为: %.2f\n" , ans);
            }
            else cout << "结果计算有误! " << endl;
        }
        else cout << "输入的算式有误! " << endl;
        cout << "请输入表达式: ";
        getline(cin , name);
    }
    system("pause");
}