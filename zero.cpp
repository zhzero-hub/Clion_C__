//
// Created by Z_HAO on 2020/2/5.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <regex>
using namespace std;

template <typename T>
class func
{
public:
    void operator()(const T &a) {//仿函数
        cout << a << ": " << a + 1 << endl;
    }
};
using Fun = func<int>;//using 声明模板

class Node
{
    vector<int> a;
    int size = 0;
public:
    Node() {
        cout << "Default constructor" << endl;
    }
    Node(const initializer_list<int> &t): Node() { //初始化列表 + 委托构造函数
        cout << "Initializer list constructor" << endl;
        for(const auto &x: t) {
            a.push_back(x);
            cout << x << ' ';
        }
        cout << endl;
        size = a.size();
    }

    auto begin()-> decltype(a.begin()) {//decltype推断返回类型
        return a.begin();
    }

    auto end()-> decltype(a.end()) {
        return a.end();
    }

    void Do() {
        for_each(a.begin() , a.end() , func<decltype(*a.begin())>());
        //for_each(a.begin() , a.end() , Fun());//使用using的用法
    }

    void count(int x) {
        int n = count_if(a.begin() , a.end() , [&x](int t) mutable-> bool {return t > x;});
        //每当定义一个lambda表达式后，编译器会自动生成一个匿名类（这个类重载了()运算符），我们称为闭包类型（closure type）
        //mutable 可修改变量
        //照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量的值的。而mutable的作用，就在于取消operator()的const。
        //仿函数的语法糖
        cout << endl;
        cout << "> x: " << n << endl;
    }

    function<bool(int)> getFilter() {
        return [this](int value)->bool {
            cout << value << endl;
            return this->size % value == 0;
        };
    }
};

template <typename T = int , typename U = int>//默认模板参数
auto add(T t , U u)-> decltype(t + u) {
    return t + u;
}

int main(int argc , char **argv)
{
    string name = R"(\ \\ \n)";
    cout << name << endl;
    Node x{1,2,5,80,81,8,24,15,52,26,128};
    int a = 10;
    double b = 15.25;
    auto c = add(a , b);
    cout << c << ' ' << typeid(x).name() << endl;
    x.Do();
    x.count(10);
    int per[] = {1 , 2 , 3};
    do {
        for_each(per , per + 3 , [](const int &x)->void {cout << x << ' ';});
        cout << endl;
    }while(next_permutation(per , per + sizeof(per) / sizeof(per[0])));
    string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    // 在 C++ 中 `\` 会被作为字符串内的转义符，为使 `\.` 作为正则表达式传递进去生效，需要对 `\` 进行二次转义，从而有 `\\.`
    regex txt_regex("[a-z]+\\.txt");
    for (const auto &fname: fnames)
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;
}
