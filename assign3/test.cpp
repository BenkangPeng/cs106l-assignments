#include"class.h"
#include<iostream>

int main(){
    Polynomial p1{1 , -2 , 3};//initializer list
    Polynomial p2{2 , 0 , -2 , 3.14 , -6};

    Polynomial p3;//default constructor
    Polynomial p4 = p1;//copy constructor
    p3 = p2;//copy assignment
    
    p3 += p4;//+=
    p4 -= p2;//-=
    Polynomial p5 = p3;
    p5 *= p4;

    std::cout << p2 << std::endl;
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;
    
    p5.set_degree(4);
    std::cout << p5 << std::endl;
}