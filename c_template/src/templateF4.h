#include <iostream>
using namespace std;

//#9
void Swap(int a, int b);

template <typename T>
void Swap(T a, T b){
    cout << "template function" << endl;
}

template<> 
void Swap(int a, int b);