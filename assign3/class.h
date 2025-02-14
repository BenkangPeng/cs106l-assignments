#pragma once
#include<initializer_list>
#include<ostream>
#include<vector>
class Polynomial{

private:
    int degree;  //the highest degree, degree = coeff.size() - 1
    double* coeff;//coefficient

    std::vector<double> coeff2vec()const;

public:

    //default constructor
    Polynomial();

    Polynomial(const std::initializer_list<double>& L);

    Polynomial(const std::vector<double>& L);

    //copy constructor
    Polynomial(const Polynomial& other);

    //copy assignment
    Polynomial& operator=(const Polynomial& other);

    //destructor
    ~Polynomial();

    //Iterator
    using iterator = double*;
    using const_iterator = const double*;
    iterator begin();
    iterator end();
    const_iterator begin()const;//cannot overload functions distinguished by return type alone
    const_iterator end()const;

    //overload operator
    friend Polynomial operator+(const Polynomial& lhs , const Polynomial& rhs);
    friend Polynomial operator-(const Polynomial& lhs , const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs , const Polynomial& rhs);
    
    friend std::ostream& operator<<(std::ostream& os , const Polynomial& rhs);

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    //get private coefficient
    double* get_coeff()const;

    //set private coefficient
    void set_degree(int new_degree);
};