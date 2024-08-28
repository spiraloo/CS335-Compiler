#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<stack>

class A{
    int a;
    int b;
    public:
    A(int a, int b){
        this->a = a;
        this->b = b;
    }
    A(){
    }
    void print(){
        std::cout << "a: " << a << " b: " << b << std::endl;
    }
    void setA(int a){
        this->a = a;
    }   
    void setB(int b){
        this->b = b;
    }
};
class B : public A{
    int c;
    public :
    void print1(){
        print();
        // std::cout << "c: " << c << std::endl;
    }
};
int main(){
    B b;
    b.setA(10);
    b.setB(20);
    b.print1();
    return 0;
}