#include<stack>
#include<queue>
#include<map>
#include<iostream>
using namespace std;
map<char,int> w;    //��ʾ����������С 
int sum;
struct Node{
    int num;//����
    char op;//����
    bool flag;//true��ʾ���֣�false��ʾ����
};
typedef struct Node node;
stack<node> s;      //ջ 
queue<node> q;     //���� 
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
        if(p[i]=='('){      //��������ջ
            cout<<1<<endl;
            n.flag=false;
            n.op=p[i];
            s.push(n);
        }
        else if(p[i]==')'){    //��ջֱ�������� ��ջ��������������Ų������У�
            cout<<2<<endl;
            while (!s.empty() && s.top().op!= '('){
                q.push(s.top());
                s.pop();
            }
            s.pop();
        }
        else if(p[i]>='0'&&p[i]<='9'){     //���ֽ�ջ
            cout<<3<<endl;
            n.flag=true;
            n.num=p[i]-'0';
            i++;
            while(i <sum && p[i] >= '0'&&p[i] <= '9'){    //��ֹ��λ��
                n.num = n.num * 10 + (p[i] - '0');
                i++;
            }
            i --;
            q.push(n);
            continue;
        }
        else{
            cout<<4<<endl;
            n.flag = false;      //����ʱ����֤ջͷ�ķ������㼶���ڻ������������
            while (!s.empty() && w[s.top().op] >= w[p[i]]){
                q.push(s.top());
                s.pop();
            }
            n.op=p[i];
            s.push(n);
        }
    }
    while(!s.empty()){    //��ջ ȫ��ѹ������
        n=s.top();
        q.push(n);
        s.pop();
        cout<<q.size()<<endl;
    }
}
void Calculate(){    //���� 
    int a,b;
    node m,n;
    while(!q.empty()){
        m=q.front();
        q.pop();
        if(m.flag==true)
            s.push(m);
        else if(m.flag==false){    //���������ǰ��������
            b = s.top().num;
            s.pop();//�����ڶ�λ����
            a = s.top().num;
            s.pop();//������һλ����
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
    cout<<s.top().num;    //�����
}
int main(){
    char ch;
    w['+'] = w['-'] = 1;//ͨ��map��ֵ
    w['*'] = w['/'] = 2;
    sum=0;
    cout<<"��������ʽ������Ĭ�ϲ�����1000\n";
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