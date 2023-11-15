#include <iostream>
using namespace std;

class CGirl{
public:
    int rank;

    CGirl(){}

    template <typename T>
    CGirl(T a){
        cout << "a=" << a << endl;
    }

    template <typename T>
    void show(T b){
        cout << "b=" << b << endl;
    }
};

//#7
template <typename T>
void Swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
    cout << "call the Swap(T& a, T& b)" << endl;
}
// template<> void Swap<CGirl>(CGirl &g1, CGirl &g2){} 和下面一样
template<> void Swap(CGirl &g1, CGirl &g2){
    int tmp = g1.rank;
    g1.rank = g2.rank;
    g2.rank = tmp;
    cout << "call the Swap(CGirl &g1, CGirl &g2)" << endl;
}

int main(){
    CGirl g(5);
    g.show("hello!");

    //#7
    CGirl g1,g2;
    g1.rank = 1;
    g2.rank = 2;
    Swap(g1,g2);
}
