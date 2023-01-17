//
//  Function.cpp
//  task3
//
//  Created by VolkSeriy on 27.11.2022.
//

#include "Function.hpp"
#include <cmath>


//double ident::operator()(double x) const {
//    return x * coef;
//}
//
//double ident::GetDeriv(double x) const {
//    return coef;
//}


polynomial::polynomial() {
    
}

polynomial::polynomial(double coef_) {
    coeficients = {coef_};
}

polynomial::polynomial(std::initializer_list<double> lst) {
    coeficients = std::vector<double>(lst.begin(), lst.end());
}


std::shared_ptr<TFunction> polynomial::get_shared() const{
    return std::make_shared<polynomial>(*this);
}


double polynomial::GetDeriv(double point) const{
    double deriv = 0;
    for (long i = 0; i < coeficients.size(); i++) {
        deriv += i * coeficients[i] * pow(point, i - 1);
    }
    return deriv;
}

double polynomial::operator()(double point) const{
    double value = 0;
    for (long i = 0; i < coeficients.size(); i++) {
        value += coeficients[i] * pow(point, i);
    }
    return value;
}

std::string polynomial::to_string() const {
    std::string str = "";
    for (long i = 0; i < coeficients.size(); i++) {
        str += std::to_string((int)coeficients[i]) + "x^" + std::to_string(i) + " + ";
    }
    
    return str.substr(0, str.size() - 3);
}




exp__::exp__(){
    coefficient = 0;
}

exp__::exp__(double coef_out){
    coefficient = coef_out;
}

exp__::exp__(std::initializer_list<double> exp_out) {
    if (exp_out.size() == 1) {
        coefficient = *(exp_out.begin());
    } else {
        throw std::invalid_argument("exp can be only init by 1 param");
    }
}

std::string exp__::to_string() const{
    return "exp(" + std::to_string((int)coefficient) + "*x)";
}

double exp__::operator()(double point) const {
    return exp(coefficient * point);
}

std::shared_ptr<TFunction> exp__::get_shared() const{
    return std::make_shared<exp__>(*this);
}

double exp__::GetDeriv(double point) const {
    return coefficient * exp(coefficient * point);
}

//Expression::Expression(const TFunction& left_out, const TFunction& right_out, std::string type_oper_out){
//    left = std::make_shared<Expression>(left_out);
//    right = std::make_shared<Expression>(right_out);
//    type_oper = type_oper_out;
//}





double Expression::GetDeriv(double point) const {
//    switch (GetType()){
//        case "+":
//
//            break;
//        case "-":
//
//            break;
//        case "*":
//
//            break;
//        case "/":
//
//            break;
//
//    }
    std::string tmp_type = this->GetType();
    if (tmp_type == "+"){
        return (*this->left).GetDeriv(point) + (*this->right).GetDeriv(point);
    }
    else if (tmp_type == "-"){
        return (*this->left).GetDeriv(point) - (*this->right).GetDeriv(point);
    }
    else if (tmp_type == "*"){
        return (*this->left).GetDeriv(point) * (*this->right)(point) +
                (*this->left)(point) * (*this->right).GetDeriv(point);
    }
    else if (tmp_type == "/"){
        return ((*this->left).GetDeriv(point) * (*this->right)(point) -
                (*this->left)(point) * (*this->right).GetDeriv(point))/((*this->left)(point) * (*this->right)(point));
    }
    else{
        throw;
    }
}

std::string Expression::to_string() const {
    std::string tmp_type = this->GetType();
    if (tmp_type == "+"){
        return (*this->left).to_string() + " + " + (*this->right).to_string();
    }
    else if (tmp_type == "-"){
        return (*this->left).to_string() + " - " + (*this->right).to_string();
    }
    else if (tmp_type == "/"){
        return (*this->left).to_string() + " / " + (*this->right).to_string();
    }
    else if (tmp_type == "*"){
        return (*this->left).to_string() + " * " + (*this->right).to_string();
    }
    else{
        throw;
    }
}

double Expression::operator()(double point) const {
    std::string tmp_type = this->GetType();
    if (tmp_type == "+"){
        return (*this->left)(point) + (*this->right)(point);
    }
    else if (tmp_type == "-"){
        return (*this->left)(point) - (*this->right)(point);
    }
    else if (tmp_type == "/"){
        return (*this->left)(point) / (*this->right)(point);
    }
    else if (tmp_type == "*"){
        return (*this->left)(point) * (*this->right)(point);
    }
    else{
        throw;
    }
    
}

std::shared_ptr<TFunction> Expression::get_shared() const{
    return std::make_shared<Expression>(*left, *right, type_oper);
}


std::shared_ptr<TFunction> operator + (TFunction& left_out, TFunction& right_out){
   return std::make_shared<Expression>( Expression(left_out, right_out, "+") );
}

std::shared_ptr<TFunction> operator - (TFunction& left_out, TFunction& right_out){
   return std::make_shared<Expression>( Expression(left_out, right_out, "-") );
}

std::shared_ptr<TFunction> operator * (TFunction& left_out, TFunction& right_out){
   return std::make_shared<Expression>( Expression(left_out, right_out, "*") );
}

std::shared_ptr<TFunction> operator / (TFunction& left_out, TFunction& right_out){
   return std::make_shared<Expression>( Expression(left_out, right_out, "/") );
}


