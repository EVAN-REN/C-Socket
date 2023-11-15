#include <iostream>
using namespace std;

//create stack by template class
template <class DataType>
class Stack{
private:
    DataType *items;
    int stacksize;
    int top;
public:
    Stack(int size):stacksize(size),top(0){
        items = new DataType[stacksize];
    }
    ~Stack(){
        delete[] items;
        items = nullptr;
    }

    bool isempty() const{
        return top == 0;
    }
    bool isfull() const{
        return top == stacksize;
    }
    bool push(const DataType& item){
        if(top < stacksize){
            items[top++] = item;
            return true;
        }
        return false;
    }
    bool pop(DataType& item){
        if(top > 0){
            item = items[--top];
            return true;
        }
        return false;
    }
 };

 int main(){
    Stack<string> ss(5);
    ss.push("1");
    ss.push("2");
    ss.push("3");
    ss.push("4");
    ss.push("5");

    string item;
    while(!ss.isempty()){
        ss.pop(item);
        cout << "item=" << item << endl;
    }
 }