#include"class.h"
#include<algorithm>
#include<cmath>
//default constructor
Polynomial::Polynomial():degree(-1){}

Polynomial::Polynomial(const std::initializer_list<double>& L):
            degree(L.size()-1) , coeff(new double[degree+1]){
    
    std::copy(L.begin(), L.end() , begin());
}

Polynomial::Polynomial(const std::vector<double>& L):
            degree(L.size()-1) , coeff(new double[degree+1]){
            
    std::copy(L.begin() , L.end() , begin());
}

//copy constructor
Polynomial::Polynomial(const Polynomial& other):
            degree(other.degree) , coeff(new double[degree+1]){
            
    std::copy(other.begin() , other.end() , begin());
    //std::copy takes const_iterator as parameters, that's why we must define const_iterator begin() and end() 
}

//copy assignment
Polynomial& Polynomial::operator=(const Polynomial& other){
    if(this == &other){
        return *this;
    }

    if(degree != -1){
        delete[] coeff;
    }
    
    degree = other.degree;

    if(other.degree != -1){
        coeff = new double[degree+1];
        std::copy(other.begin() , other.end() , begin());
    }


    return *this;

}

//destructor
Polynomial::~Polynomial(){
    delete[] coeff;
}

//Iterator
Polynomial::iterator Polynomial::begin(){
    return coeff;
}

Polynomial::iterator Polynomial::end(){
    return coeff + degree + 1;
}

Polynomial::const_iterator Polynomial::begin()const{
    return coeff;
}

Polynomial::const_iterator Polynomial::end()const{
    return coeff + degree + 1;
}

//private member function
std::vector<double> Polynomial::coeff2vec()const{
    std::vector<double> V;
    std::copy(begin() , end() , std::back_inserter(V));

    return V;
}


//overload operator
Polynomial& Polynomial::operator+=(const Polynomial& other){
    if(degree > other.degree){
        for(int i = 0 , j = 0 ; i < degree+1 ; ++i , ++j){
            double other_coeff = (j <= other.degree) ? other.coeff[j] : 0;
            coeff[i] += other_coeff;
        }

        return *this;
    }
    else if(degree < other.degree){
        int new_degree = other.degree;
        double* new_coeff = new double[new_degree+1];
        std::copy(other.coeff , other.coeff + other.degree + 1 , new_coeff);
        
        for(int i = 0 , j = 0 ; i < new_degree + 1 ; ++i , ++j){
            double _coeff = (j <= degree) ? coeff[j] : 0;
            new_coeff[i] += _coeff;
        }

        delete[] coeff;
        coeff = new_coeff;
        degree = new_degree;

        return *this;
    }
    else{
        for(int i = 0 ; i < degree+1 ; ++i){
            coeff[i] += other.coeff[i];
        }
        return *this;
    }
}

Polynomial& Polynomial::operator-=(const Polynomial& other){
    if(degree > other.degree){
        for(int i = 0 , j = 0 ; i < degree+1 ; ++i , ++j){
            double other_coeff = (j <= other.degree) ? other.coeff[j] : 0;
            coeff[i] -= other_coeff;
        }

        return *this;
    }
    else if(degree < other.degree){
        int new_degree = other.degree;
        double* new_coeff = new double[new_degree+1];
        std::copy(other.coeff , other.coeff + other.degree + 1 , new_coeff);
        
        for(int i = 0 , j = 0 ; i < new_degree + 1 ; ++i , ++j){
            double _coeff = (j <= degree) ? coeff[j] : 0;
            new_coeff[i] = _coeff - new_coeff[i];
        }

        delete[] coeff;
        coeff = new_coeff;
        degree = new_degree;

        return *this;
    }
    else{
        for(int i = 0 ; i < degree+1 ; ++i){
            coeff[i] -= other.coeff[i];
        }
        return *this;
    }
}
Polynomial& Polynomial::operator*=(const Polynomial& other){
    int degree2 = other.degree;
    int new_degree = degree + degree2;

    double* new_coeff = new double[new_degree + 1];
    for(int i = 0 ; i <= degree ; ++i){
        for(int j = 0 ; j <= degree2 ; ++j){
            new_coeff[i+j] = coeff[i] * other.coeff[j];
        }
    }

    delete[] coeff;
    coeff = new_coeff;
    degree = new_degree;
    return *this; 
}

Polynomial operator+(const Polynomial& lhs , const Polynomial& rhs){
    int lhs_degree = lhs.degree , rhs_degree = rhs.degree;
    int new_degree = lhs_degree > rhs_degree ? lhs_degree : rhs_degree;
    std::vector<double> new_coeff(new_degree+1 , 0);

    double lhs_coeff , rhs_coeff;
    
    for(int i = 0 ; i <= new_degree ; ++i){
        lhs_coeff = i <= lhs_degree ? lhs.coeff[i] : 0;
        rhs_coeff = i <= rhs_degree ? rhs.coeff[i] : 0;

        new_coeff[i] = lhs_coeff + rhs_coeff; 
    }

    return Polynomial(new_coeff);
}
Polynomial operator-(const Polynomial& lhs , const Polynomial& rhs){
    int lhs_degree = lhs.degree , rhs_degree = rhs.degree;
    int new_degree = lhs_degree > rhs_degree ? lhs_degree : rhs_degree;
    std::vector<double> new_coeff(new_degree+1 , 0);

    double lhs_coeff , rhs_coeff;
    
    for(int i = 0 ; i <= new_degree ; ++i){
        lhs_coeff = i <= lhs_degree ? lhs.coeff[i] : 0;
        rhs_coeff = i <= rhs_degree ? rhs.coeff[i] : 0;

        new_coeff[i] = lhs_coeff - rhs_coeff; 
    }

    return Polynomial(new_coeff);
}
Polynomial operator*(const Polynomial& lhs , const Polynomial& rhs){
    int degree1 = lhs.degree;
    int degree2 = rhs.degree;
    int new_degree = degree1 + degree2;

    std::vector<double> new_coeff(new_degree + 1 , 0);

    for(int i = 0 ; i <= degree1 ; ++i){
        for(int j = 0 ; j <= degree2 ; ++j){
            new_coeff[i+j] = lhs.coeff[i] * rhs.coeff[j];
        }
    }



    return Polynomial(new_coeff); 
}

std::ostream& operator<<(std::ostream& os , const Polynomial& rhs){
    
    const double EPSILON = 1e-6;

    os << rhs.coeff[0];

    for(int i = 1 ; i < rhs.degree + 1 ; ++i){
        double _coeff = rhs.coeff[i];
        if(_coeff > EPSILON){// >0
            os << '+' << _coeff << 'x' << '^' << i;
        }
        else if(_coeff < -EPSILON){// <0
            os << _coeff << 'x' << '^' << i;
        }
    }

    return os;
}

double* Polynomial::get_coeff()const{
    double* res = new double[degree+1];
    std::copy(begin() , end() , res);
    return res;
}

void Polynomial::set_degree(int new_degree){
    if(new_degree < 0){
        throw std::domain_error("cann't set degree of Polynomial to negtive");
    }

    if(new_degree > degree){
        double* new_coeff = new double[new_degree+1]();
        std::copy(coeff , coeff+degree+1 , new_coeff);

        delete[] coeff;
        coeff = new_coeff;
    }
    else{
        double* new_coeff = new double[new_degree+1]();
        std::copy(coeff , coeff+new_degree+1 , new_coeff);

        delete[] coeff;
        coeff = new_coeff;
    }

    degree = new_degree;

}