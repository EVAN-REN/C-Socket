#include <iostream>
using namespace std;



template <typename T>
void Swap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void Swap(){
    cout << "swap function" << endl;
}

template <typename T>
T Add(T a, T b){
    return a + b;
}

// #4
template <typename T1, typename T2>
void show(T1 no, T2 message){
    cout << "no:" << no << ", message:" <<message << endl;
}

//#5
template <typename T>
void func(T a){
    cout << "func(T a)" << endl;
}

template <typename T1, typename T2>
void func(T1 a, T2 b){
    cout << "func(T1 a, T2 b)" << endl;
}

template <typename T1, typename T2>
void func(T1 a, T2 b, int c){
    cout << "func(T1 a, T2 b, int c)" << endl;
}

int main(){
    int a1 = 10, b1 = 30;
    Swap(a1, b1);
    Swap<int>(a1,b1);
    cout << "a1=" << a1 << ",b1=" << b1 << endl;

    //#2必须明确类型，没有类型要显示指定
    Swap<int>();

    //#3
    char a2 = 10;
    int b2 = 20;
    int c2 = Add<int>(a2,b2);
    cout << "c2=" << c2 << endl;

    //#4
    short no = 4;
    char* message = "multiple template variable";
    show(no, message);

    //#5
    func(1);
    func(1,2);
    func(1,2,3);
}
