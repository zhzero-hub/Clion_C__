#include<iostream>
#include<string>
#include<iterator>
#include<vector>
using namespace std;

string Plus_1(string x)//字符串加法，把数字字符串所表示的数+1
{
    unsigned int p = x.size() - 1;
    if(x[p] >= '0' && x[p] < '9')//最后一位不是9，不需要考虑进位，直接+1
    {
        x[p] ++;
        return x;
    }
    else
    {
        while(x[p] == '9')//找到不是9的那一位
        {
            if(p == 0)//全都是9，即9999……
            {
                x[p] = '1';
                x.push_back('0');//将字符串变为10000……
                return x;
            }
            else
            {
                x[p] = '0';//将这一位变成0
                p --;//继续看下一位
            }
        }
        x[p] ++;//进位
        return x;
    }
}

string Plus_2(string x)//字符串加法，+2，本质是两个+1
{
    string temp = Plus_1(move(x));
    return Plus_1(temp);
}

bool Check(const string& t , int n , int &flag , vector<string> &q , string &extra)//检查输入的字符串是否符合要求
{//对字符串t，以n位分割字符串数字，flag表示过程中出现的漏掉数字的个数，q用来存储满足条件的字符串数字，extra为漏掉的数字
    int size = t.size();
    int i = 0;
    while(i + n < size)
    {
        string temp , temp1 , temp2;
        if(i + n >= size)temp = t.substr(i , size);//一次取n位，如果超过最后一位就取到最后一位结束
        else temp = t.substr(i , n);
        temp1 = Plus_1(temp);//temp1是temp字符串+1的结果
        i += n;
        n = temp1.size();//如果出现了999……的情况，那么接下来取的n位应该变成n+1位
        if(i + n >= size)temp2 = t.substr(i , size);
        else temp2 = t.substr(i , n);
        if(temp2 != temp1)//前一个数和后一个数不是+1的关系
        {
            if(flag)return false;//前面已经出现了一个漏掉的数
            else
            {
                extra = temp1;
                temp1 = Plus_2(temp);
                if(n != temp1.size())//如果这两个数是998、1000那么取temp2的时候n也应该+1
                {
                    n = temp1.size();
                    temp2 = t.substr(i , n);
                }
                if(temp2 != temp1)return false;//不是+2的关系
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
        for(int i = size / 2;i >= 1;i --)//因为至少要有两个数，所以一个数至多是size/2位
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
        extra.clear();//所有内容全部初始化
        cout << "请输入序列: ";
        cin >> x;
    }
    system("pause");
}