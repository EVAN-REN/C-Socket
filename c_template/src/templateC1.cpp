#include <iostream>
using namespace std;

//#1 #3
template <class T1, class T2 = string>
class AA
{
private:
    /* data */
public:
    T1 m_a;
    T2 m_b;

    AA(){}

    AA(T1 a, T2 b):m_a(a), m_b(b){}

    //#2
    T1 geta(){
        T1 a = 2;
        return m_a + a;
    }

    T2 getb(){
        return m_b;
    }

    T1 geta2();
};

//#4
template <class T1,class T2>
T1 AA<T1,T2>::geta2(){
    return m_a;
}

int main(){

    AA<int,string> a;
    a.m_a = 20;
    a.m_b = "hello";
    cout << "a.geta()=" << a.geta() << endl;
    cout << "a.getb()=" << a.getb() << endl;

    //#5
    AA<int,string> *b = new AA<int,string>(3,"world");
    cout << "b->geta()=" << b->geta() << endl;
    cout << "b->getb()=" << b->getb() << endl;
    delete(b);
}
