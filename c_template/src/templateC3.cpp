#include <iostream>
using namespace std;

//create array by template class
template <class T, int len = 10>
class Array{
private:
    T items[len];
public:
    Array(){}

    ~Array(){}
    // can change the elements in array
    T& operator[](int i){
        return items[i];
    }
    // can't change the elements in array
    const T& operator[](int i) const {
        return items[i];
    }
};


//create vector by template class
template <class T>
class Vector{
private:
    T* items;
    int len;
public:
    Vector(int size = 10):len(size){
        items = new T[len];
    }

    ~Vector(){
        delete[] items;
        items = nullptr;
    }

    void resize(int size){
        if(size <= len) return;
        T* tmp = new T[size];
        for(int i = 0; i < len; i++){
            tmp[i] = items[i];
        }
        delete[] items;
        items = tmp;
        len = size;
    }

    int size() const {
        return len;
    }
    // can change the elements in array
    T& operator[](int i){
        if(i >= len){
            resize(i + 10);
        }
        return items[i];
    }
    // can't change the elements in array
    const T& operator[](int i) const {
        return items[i];
    }
};

int main(){
    Array<string, 5> a;
    a[0] = "hello ";
    a[1] = "world";
    a[2] = "!";
    cout << a[0] << a[1] << a[2] << endl;

    Vector<string> b(1);
    b[0] = 1;
    b[1] = 2;
    cout << b.size() << endl;
}