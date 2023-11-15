#include <iostream>
using namespace std;

template <class DataType>
class Stack{
private:
    DataType *items;
    int stacksize;
    int top;
public:
    Stack(int size = 3):stacksize(size),top(0){
        items = new DataType[stacksize];
    }
    ~Stack(){
        delete[] items;
        items = nullptr;
    }

    //#q1:重载赋值运算符函数，实现深拷贝，解决vector扩充复制错误的问题
    Stack& operator=(const Stack& v){
        delete[] items;
        stacksize = v.stacksize;
        items = new DataType[stacksize];
        for(int i = 0; i < stacksize; i++){
            items[i] = v.items[i];
        }
        top = v.top;
        return *this;
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
            //#q2:出错
            item = items[--top];
            return true;
        }
        return false;
    }

 };

template <class T>
class Vector{
private:
    T* items;
    int len;
public:
    Vector(int size = 2):len(size){
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
            resize(i + 1);
        }
        return items[i];
    }
    // can't change the elements in array
    const T& operator[](int i) const {
        return items[i];
    }

    //#q2:重载赋值运算符函数，实现深拷贝，解决pop复制错误的问题
    Vector& operator=(const Vector &v){
        delete[] items;
        len = v.len;
        items = new T[len];
        for(int i = 0; i < len; i++){
            items[i] = v.items[i];
        }
        return *this;
    }
};


int main(){
    //#7
    //Vector容器的大小缺省值为2，Stack容器的大小的缺省值为3
    //创建vector容器，容器中的元素用stack
    Vector<Stack<string>> vs;

    //手工的往容器中插入数据
    vs[0].push("s11");
    vs[0].push("s12");
    vs[0].push("s13");
    vs[1].push("s21");
    vs[1].push("s22");
    vs[1].push("s23");
//q1:会出错，原因是因为自定义vector在扩展内存时，对于stack类的元素复制用的是浅拷贝，在delete后会找不到
    vs[2].push("s31");
    vs[2].push("s32");

    //用嵌套的循环，把容器中的数据显示出来
    for(int i = 0; i < vs.size(); i++){
        while(!vs[i].isempty()){
            string item;
            vs[i].pop(item);
            cout << "item = " << item << endl;
        }
    }

    cout << "---------------------------" << endl;

    Stack<Vector<string>> sv;
    Vector<string> tmp;
    tmp[0] = "v11";
    tmp[1] = "v12";
    sv.push(tmp);
    tmp[0] = "v21";
    tmp[1] = "v22";
    sv.push(tmp);
    tmp[0] = "v31";
    tmp[1] = "v32";
    tmp[2] = "v33";
    tmp[3] = "v34";
    sv.push(tmp);

    //用嵌套的循环，把容器中的数据显示出来
    while(!sv.isempty()){
        sv.pop(tmp);
        for(int i = 0; i < tmp.size(); i++){
            cout << "tmp = " << tmp[i] << endl;
        }
    }
     cout << "---------------------------" << endl;
    
    //#8
    Vector<Vector<string>> vv;
    vv[0][0] = "v11";
    vv[0][1] = "v12";
    vv[0][2] = "v13";
    vv[1][0] = "v21";
    vv[1][1] = "v22";
    vv[2][0] = "v31";
    vv[2][1] = "v32";
    vv[2][2] = "v33";
    vv[2][3] = "v34";

    for(int i = 0; i < vv.size(); i++){
        for(int j = 0; j < vv[i].size(); j++){
            cout << "res = " << vv[i][j] << endl;
        }
    }
}