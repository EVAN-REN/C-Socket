#include <iostream>
using namespace std;

int func(){
    cout << "call func() function" << endl;
    return 3;
}

//c++14中可以不用 -> decltype(x + y)
template <typename T1, typename T2>
auto test(T1 x, T2 y) -> decltype(x + y){
    // auto tmp = x + y;
    decltype(x + y) tmp = x + y;
    cout << "tmp=" << tmp << endl;

    return tmp;
}

int main(){
    //#13
    short a = 5;
    decltype(a) da;

    //#10
    short *b;
    decltype(b) db;
    short& c = a;
    decltype(c) dc = a;

    //#11
    decltype(func()) d;
    decltype(func) *e = func;

    //#12 这里df,dg,dh是引用类型
    int f;
    decltype(++f) df = f;
    int g;
    decltype((g)) dg = g;
    decltype((func)) dh = func;
    dh();

    short i = 3;
    char j = '2';
    test(i,j);
}