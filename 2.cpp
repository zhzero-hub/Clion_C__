#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

bool res(string &name , stack<char> &p , queue<string> &q)
{
    for(auto x = name.begin();x < name.end();x ++)
    {
        if((*x >= '0' && *x <= '9') || *x == '.')//�����һ�����֣���һֱ���������ֽ�������������ֵ��ַ�����ʽ���
        {
            string num;
            int time;//time��ʾС������ֵĴ�������Ϊһ�����ֲ��ܰ�������С����
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
                        return false;//����������С����
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
            if(*x == '(')p.push(*x);//���Ϊ�����ţ�ֱ�����
            else if(*x == ')')//���Ϊ�����ţ��ͽ�ջ��һֱ�������ŵ������������
            {
                char ch = p.top();
                p.pop();
                while(ch != '(')
                {
                    string temp(1 , ch);
                    q.push(temp);
                    if(p.empty())
                    {
                        return false;//һֱ��ջ�ն�û�����������ţ�˵�����Ų�ƥ��
                    }
                    ch = p.top();
                    p.pop();
                }
            }
            else if(*x == '*' || *x == '/')//�˳�ֱ����ջ
            {
                p.push(*x);
            }
            else if(*x == '+' || *x == '-')//�����Ӽ�����ջ��һֱ�������ŵ������ַ���ӣ�Ȼ�����������
            {
                if(p.empty())//���ջ������ǿյģ���������ջ
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
            else return false;//�����������κ������˵�������������ַ�
        }
    }
    while(!p.empty())//���ջ��Ԫ���������
    {
        char ch = p.top();
        p.pop();
        string temp(1 , ch);
        q.push(temp);
    }
    return true;//��׺���ʽת�����
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
            ans = false;//��������Ϊ0
            return 0;
        }
        return a / b;
    }
    return 0;
}

double res_double(string &t)//���ַ���������ת����double��
{
    double ans = 0;
    auto pos = t.find('.');
    if(pos == -1)//û��С���㣬˵��������
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
        for(int p = 0;p < pos;p ++)//�ⲿ������������
        {
            double temp = t[p] - '0';
            ans *= 10;
            ans += temp;
        }
        for(unsigned int p = t.size() - 1;p > pos;p --)//�ⲿ����С������
        {
            double temp = t[p] - '0';
            temp /= 10;
            ans += temp;
        }
    }
    return ans;
}

bool Ans(queue<string> &q , double &ans)//���ݺ�׺���ʽ��ֵ
{
    stack<double> p;//������ջ
    while(!q.empty())
    {
        string x = q.front();
        q.pop();
        if(x == "+" || x == "-" || x == "*" || x == "/")//����������������м���
        {
            if(p.empty())return false;//ջ��û��Ԫ�أ�˵�����ʽ����
            double b = p.top();//�ȳ�ջ���Ǻ���һ���������ջ����ǰ��һ����
            p.pop();
            if(p.empty())return false;
            double a = p.top();
            p.pop();
            bool check = true;
            double c = Cal(a , b , check , x);//����󽫵õ���ֵ����
            if(check)p.push(c);
            else return false;//����Ϊ0
        }
        else
        {
            double temp = res_double(x);
            p.push(temp);
        }
    }
    if(p.size() == 1)ans = p.top();//�������ı��ʽ��ȷ�����ջ��Ӧ��ֻ��һ��Ԫ��
    else return false;
    return true;
}

int main()
{
    string name;
    double ans = 0;
    cout << "��������ʽ: ";
    getline(cin , name);
    while(name != "#")
    {
        stack<char> p;
        queue<string> q;
        if(res(name , p , q))
        {
            queue<string> out(q);//out���г�ʼ��Ϊq����q��һ�����ƣ����������׺���ʽ
            cout << "��׺���ʽΪ: ";
            while(!out.empty())
            {
                cout << out.front() << ' ';
                out.pop();
            }
            cout << endl;
            bool check = Ans(q , ans);//check�жϼ����Ƿ����Ҫ��
            if(check)
            {
                printf("���Ϊ: %.2f\n" , ans);
            }
            else cout << "�����������! " << endl;
        }
        else cout << "�������ʽ����! " << endl;
        cout << "��������ʽ: ";
        getline(cin , name);
    }
    system("pause");
}