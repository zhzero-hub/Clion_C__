#include<stack>
#include<queue>
#include<map>
#include<iostream>
using namespace std;
map<char,int> w;    //表示运算符级别大小 
int sum;
struct Node{
    int num;//数字
    char op;//符号
    bool flag;//true表示数字，false表示符号
};
typedef struct Node node;
stack<node> s;      //栈 
queue<node> q;     //队列 
void show(){
    if(q.empty())
        return;
    node x,y;
    x=q.front();
    if(x.flag==true)	cout<<x.num<<' ';
    else	cout<<x.op<<' ';
    q.push(x);
    q.pop();
    while(x.num!=q.front().num){
        y=q.front();
        if(y.flag==true)	cout<<y.num<<' ';
        else	cout<<y.op<<' ';
        q.push(y);
        q.pop();
    }
    cout<<endl;
}
void Change(char *p){
    int i=0;
    node n;
    for(;i<sum;i++){
        if(p[i]=='('){      //“（”进栈
            cout<<1<<endl;
            n.flag=false;
            n.op=p[i];
            s.push(n);
        }
        else if(p[i]==')'){    //出栈直到”（“ 出栈（但是这个有括号不进队列）
            cout<<2<<endl;
            while (!s.empty() && s.top().op!= '('){
                q.push(s.top());
                s.pop();
            }
            s.pop();
        }
        else if(p[i]>='0'&&p[i]<='9'){     //数字进栈
            cout<<3<<endl;
            n.flag=true;
            n.num=p[i]-'0';
            i++;
            while(i <sum && p[i] >= '0'&&p[i] <= '9'){    //不止个位数
                n.num = n.num * 10 + (p[i] - '0');
                i++;
            }
            i --;
            q.push(n);
            continue;
        }
        else{
            cout<<4<<endl;
            n.flag = false;      //符号时，保证栈头的符号运算级高于或等于这个运算符
            while (!s.empty() && w[s.top().op] >= w[p[i]]){
                q.push(s.top());
                s.pop();
            }
            n.op=p[i];
            s.push(n);
        }
    }
    while(!s.empty()){    //把栈 全部压进队列
        n=s.top();
        q.push(n);
        s.pop();
        cout<<q.size()<<endl;
    }
}
void Calculate(){    //计算 
    int a,b;
    node m,n;
    while(!q.empty()){
        m=q.front();
        q.pop();
        if(m.flag==true)
            s.push(m);
        else if(m.flag==false){    //计算运算符前两个数字
            b = s.top().num;
            s.pop();//弹出第二位数字
            a = s.top().num;
            s.pop();//弹出第一位数字
            n.flag=true;
            if(m.op=='+')
                n.num=a+b;
            else if(m.op=='-')
                n.num=a-b;
            else if(m.op=='*')
                n.num=a*b;
            else	n.num=a/b;
            s.push(n);
        }
    }
    cout<<s.top().num;    //最后结果
}
int main(){
    char ch;
    w['+'] = w['-'] = 1;//通过map赋值
    w['*'] = w['/'] = 2;
    sum=0;
    cout<<"请输入表达式，长度默认不超过1000\n";
    char a[1000];
    while(1){
        cin>>ch;
        if (ch != '#'){
            a[sum]=ch;
            sum++;
        }
        if (ch == '#' && sum != 0)
            break;
    }
    Change(a);
    Calculate();
    return 0;
}