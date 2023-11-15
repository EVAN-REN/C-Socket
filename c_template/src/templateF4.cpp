#include "templateF4.h"

//#9
void Swap(int a, int b){
    cout << "ordinary function" << endl;
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