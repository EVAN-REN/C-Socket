#include <iostream>
using namespace std;

//#8
void Swap(int a, int b){
    cout << "ordinary function" << endl;
}

template <typename T>
void Swap(T a, T b){
    cout << "template function" << endl;
}

template<> 
void Swap(int a, int b){
    cout << "concrete template function" << endl;
}

int main(){
    Swap(1,2);
    Swap<>(1,2);
    Swap('a','b');
}