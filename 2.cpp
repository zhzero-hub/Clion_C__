#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

bool res(string &name , stack<char> &p , queue<string> &q)
{
    for(auto x = name.begin();x < name.end();x ++)
    {
        if((*x >= '0' && *x <= '9') || *x == '.')//如果是一个数字，就一直遍历到数字结束，将这个数字的字符串形式入队
        {
            string num;
            int time;//time表示小数点出现的次数，因为一个数字不能包含两个小数点
            if(*x == '.')time = 1;
            else time = 0;
            while((*x >= '0' && *x <= '9') || *x == '.')
            {
                num += *x;
                x ++;
                if(*x == '.')
                {
                    if(time == 1)
                    {
                        return false;//出现了两个小数点
                    }
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
            if(*x == '(')p.push(*x);//如果为左括号，直接入队
            else if(*x == ')')//如果为右括号，就将栈内一直到左括号的所有内容入队
            {
                char ch = p.top();
                p.pop();
                while(ch != '(')
                {
                    string temp(1 , ch);
                    q.push(temp);
                    if(p.empty())
                    {
                        return false;//一直到栈空都没有遇到左括号，说明括号不匹配
                    }
                    ch = p.top();
                    p.pop();
                }
            }
            else if(*x == '*' || *x == '/')//乘除直接入栈
            {
                p.push(*x);
            }
            else if(*x == '+' || *x == '-')//遇到加减，则将栈内一直到左括号的所有字符入队，然后自身再入队
            {
                if(p.empty())//如果栈本身就是空的，则自身入栈
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
            else return false;//不属于以上任何情况，说明遇到了其它字符
        }
    }
    while(!p.empty())//最后将栈内元素依次入队
    {
        char ch = p.top();
        p.pop();
        string temp(1 , ch);
        q.push(temp);
    }
    return true;//后缀表达式转换完成
}

double Cal(double &a , double &b , bool &ans , string &sig)
{
    if(sig == "+")return a + b;
    else if(sig == "-")return a - b;
    else if(sig == "*")return a * b;
    else if(sig == "/")
    {
        if(b == 0)
        {
            ans = false;//除数不能为0
            return 0;
        }
        return a / b;
    }
    return 0;
}

double res_double(string &t)//将字符串的数字转换成double型
{
    double ans = 0;
    auto pos = t.find('.');
    if(pos == -1)//没有小数点，说明是整数
    {
        for(auto x: t)
        {
            double temp = x - '0';
            ans *= 10;
            ans += temp;
        }
    }
    else
    {
        for(int p = 0;p < pos;p ++)//这部分是整数部分
        {
            double temp = t[p] - '0';
            ans *= 10;
            ans += temp;
        }
        for(unsigned int p = t.size() - 1;p > pos;p --)//这部分是小数部分
        {
            double temp = t[p] - '0';
            temp /= 10;
            ans += temp;
        }
    }
    return ans;
}

bool Ans(queue<string> &q , double &ans)//根据后缀表达式的值
{
    stack<double> p;//辅助用栈
    while(!q.empty())
    {
        string x = q.front();
        q.pop();
        if(x == "+" || x == "-" || x == "*" || x == "/")//如果是运算符，则进行计算
        {
            if(p.empty())return false;//栈中没有元素，说明表达式有误
            double b = p.top();//先出栈的是后面一个数，后出栈的是前面一个数
            p.pop();
            if(p.empty())return false;
            double a = p.top();
            p.pop();
            bool check = true;
            double c = Cal(a , b , check , x);//计算后将得到的值返回
            if(check)p.push(c);
            else return false;//除数为0
        }
        else
        {
            double temp = res_double(x);
            p.push(temp);
        }
    }
    if(p.size() == 1)ans = p.top();//如果输入的表达式正确，最后栈内应该只有一个元素
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
            queue<string> out(q);//out队列初始化为q，是q的一个复制，用于输出后缀表达式
            cout << "后缀表达式为: ";
            while(!out.empty())
            {
                cout << out.front() << ' ';
                out.pop();
            }
            cout << endl;
            bool check = Ans(q , ans);//check判断计算是否符合要求
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