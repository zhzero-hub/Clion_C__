#include<iostream>
#include<string>
#include<iterator>
#include<vector>
using namespace std;

string Plus_1(string x)
{
    unsigned int p = x.size() - 1;
    if(x[p] >= '0' && x[p] < '9')
    {
        x[p] ++;
        return x;
    }
    else
    {
        while(x[p] == '9')
        {
            if(p == 0)
            {
                x[p] = '1';
                x.push_back('0');
                return x;
            }
            else
            {
                x[p] = '0';
                p --;
            }
        }
        x[p] ++;
        return x;
    }
}

string Plus_2(string x)
{
    string temp = Plus_1(move(x));
    return Plus_1(temp);
}

bool Check(const string& t , int n , int &flag , vector<string> &q , string &extra)
{
    int size = t.size();
    int i = 0;
    while(i + n < size)
    {
        string temp , temp1 , temp2;
        if(i + n >= size)temp = t.substr(i , size);
        else temp = t.substr(i , n);
        temp1 = Plus_1(temp);
        i += n;
        n = temp1.size();
        if(i + n >= size)temp2 = t.substr(i , size);
        else temp2 = t.substr(i , n);
        if(temp2 != temp1)
        {
            if(flag)return false;
            else
            {
                extra = temp1;
                temp1 = Plus_2(temp);
                if(n != temp1.size())
                {
                    n = temp1.size();
                    temp2 = t.substr(i , n);
                }
                if(temp2 != temp1)return false;
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
    cout << "请输入序列: ";
    cin >> x;
    while(x != "#")
    {
        int size = x.size();
        for(int i = size / 2;i >= 1;i --)
        {
            ans = Check(x , i , flag , q , extra);
            if(ans)
            {
                copy(q.begin() , --q.end() , ostream_iterator<string , char>(cout , ", "));
                copy(--q.end() , q.end() , ostream_iterator<string , char>(cout , "\n"));
                if(flag)cout << "漏掉的数字为: " << extra << endl;
                break;
            }
            q.clear();
            flag = 0;
        }
        if(!ans)cout << "输入的序列有误，请重新输入! " << endl;
        x.clear();
        q.clear();
        flag = 0;
        extra.clear();
        cout << "请输入序列: ";
        cin >> x;
    }
    system("pause");
}