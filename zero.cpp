//
// Created by Z_HAO on 2020/2/5.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class func
{
public:
    void operator()(const T &a) {
        cout << a << ": " << a + 1 << endl;
    }
};

class Node
{
    vector<int> a;
    int size = 0;
public:
    Node(const initializer_list<int> &t) {
        for(const auto &x: t) {
            a.push_back(x);
            cout << x << ' ';
        }
        cout << endl;
        size = a.size();
    }

    auto begin()-> decltype(a.begin()) {
        return a.begin();
    }

    auto end()-> decltype(a.end()) {
        return a.end();
    }

    void Do() {
        for_each(a.begin() , a.end() , func<decltype(*a.begin())>());
    }
};

template <typename T , typename U>
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
}
