#include<iostream>
#include<string>
#include<iterator>
#include<vector>
using namespace std;

string Plus_1(string x)//�ַ����ӷ����������ַ�������ʾ����+1
{
    unsigned int p = x.size() - 1;
    if(x[p] >= '0' && x[p] < '9')//���һλ����9������Ҫ���ǽ�λ��ֱ��+1
    {
        x[p] ++;
        return x;
    }
    else
    {
        while(x[p] == '9')//�ҵ�����9����һλ
        {
            if(p == 0)//ȫ����9����9999����
            {
                x[p] = '1';
                x.push_back('0');//���ַ�����Ϊ10000����
                return x;
            }
            else
            {
                x[p] = '0';//����һλ���0
                p --;//��������һλ
            }
        }
        x[p] ++;//��λ
        return x;
    }
}

string Plus_2(string x)//�ַ����ӷ���+2������������+1
{
    string temp = Plus_1(move(x));
    return Plus_1(temp);
}

bool Check(const string& t , int n , int &flag , vector<string> &q , string &extra)//���������ַ����Ƿ����Ҫ��
{//���ַ���t����nλ�ָ��ַ������֣�flag��ʾ�����г��ֵ�©�����ֵĸ�����q�����洢�����������ַ������֣�extraΪ©��������
    int size = t.size();
    int i = 0;
    while(i + n < size)
    {
        string temp , temp1 , temp2;
        if(i + n >= size)temp = t.substr(i , size);//һ��ȡnλ������������һλ��ȡ�����һλ����
        else temp = t.substr(i , n);
        temp1 = Plus_1(temp);//temp1��temp�ַ���+1�Ľ��
        i += n;
        n = temp1.size();//���������999�������������ô������ȡ��nλӦ�ñ��n+1λ
        if(i + n >= size)temp2 = t.substr(i , size);
        else temp2 = t.substr(i , n);
        if(temp2 != temp1)//ǰһ�����ͺ�һ��������+1�Ĺ�ϵ
        {
            if(flag)return false;//ǰ���Ѿ�������һ��©������
            else
            {
                extra = temp1;
                temp1 = Plus_2(temp);
                if(n != temp1.size())//�������������998��1000��ôȡtemp2��ʱ��nҲӦ��+1
                {
                    n = temp1.size();
                    temp2 = t.substr(i , n);
                }
                if(temp2 != temp1)return false;//����+2�Ĺ�ϵ
                else flag = 1;
            }
        }
        q.push_back(temp);
    }
    string temp2 = t.substr(i , n);
    q.push_back(temp2);
    return true;
}

int main()
{
    string x;
    vector<string> q;
    bool ans = true;
    int flag = 0;
    string extra;
    cout << "����������: ";
    cin >> x;
    while(x != "#")
    {
        int size = x.size();
        for(int i = size / 2;i >= 1;i --)//��Ϊ����Ҫ��������������һ����������size/2λ
        {
            ans = Check(x , i , flag , q , extra);
            if(ans)
            {
                copy(q.begin() , --q.end() , ostream_iterator<string , char>(cout , ", "));
                copy(--q.end() , q.end() , ostream_iterator<string , char>(cout , "\n"));
                if(flag)cout << "©��������Ϊ: " << extra << endl;
                break;
            }
            q.clear();
            flag = 0;
        }
        if(!ans)cout << "�����������������������! " << endl;
        x.clear();
        q.clear();
        flag = 0;
        extra.clear();//��������ȫ����ʼ��
        cout << "����������: ";
        cin >> x;
    }
    system("pause");
}