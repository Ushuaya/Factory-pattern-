//
//  Function.hpp
//  task3
//
//  Created by VolkSeriy on 27.11.2022.
//

#ifndef Function_hpp
#define Function_hpp

#include <cstdio>
#include <string>
#include <vector>


class TFunction {
public:
    virtual double GetDeriv(double point) const = 0;
    virtual std::string to_string() const = 0;
    //virtual ~TFunction(){};
    virtual double operator()(double point) const = 0;
    virtual std::shared_ptr<TFunction> get_shared() const = 0;
    
};

class polynomial : public TFunction {
protected:
    std::vector<double> coeficients;
public:
    
    double GetDeriv(double point) const override;
    std::string to_string() const override;
    polynomial();
    polynomial(double coef_);
    polynomial(std::initializer_list<double> lst);
    virtual double operator()(double x) const override;
    std::shared_ptr<TFunction> get_shared() const override;
    
};

class ident : public polynomial {
public:
    double GetDeriv(double point) const override{
        return coeficients[0];
    }

    std::string to_string() const override{
        return "x*" + std::to_string(coeficients[0]);
    }
    double operator()(double point) const override{
        return point * coeficients[0];
    }
    ident(double coef_out) {
        coeficients = {coef_out};
    }
    ident(std::initializer_list<double> init_lst){
        if (init_lst.size() == 1){
            coeficients = std::vector<double>(init_lst.begin(), init_lst.end());
        }
        else{
            throw "BAN";
        }
    }
    ident(std::vector<double> lst) = delete;
    ident() {
        coeficients = {0};
    }
    std::shared_ptr<TFunction> get_shared() const override{
        return std::make_shared<ident>(*this);
    }
};

class const__ : public TFunction {
    double constant;
public:
    const__(){
        constant = 0;
    }
    const__(double counst_out): constant(counst_out){}
    
    const__(std::initializer_list<double> init_lst){
        if (init_lst.size() == 1){
            constant = std::vector<double>(init_lst.begin(), init_lst.end())[0];
        }
        else{
            throw "BAN";
        }
    }
    
    double GetDeriv(double point) const override{
        return 0;
    };
    std::string to_string() const override{
        return std::to_string(constant);
    };
    
    std::shared_ptr<TFunction> get_shared() const override{
        return std::make_shared<const__>(*this);
    }
    
    double operator()(double) const override{
        return constant;;
    }
    
};

class power : public polynomial {
public:
    power(){
        coeficients.push_back(0);
    }
    power(double coef_out) {
        for (long i = 0; i < coef_out; i++){
            coeficients.push_back(0);
        }
        coeficients.push_back(1);
    }
    
    power(std::initializer_list<double> init_lst){
        if (init_lst.size() == 1){
            auto tmp_val = std::vector<double>(init_lst.begin(), init_lst.end())[0];
            for (long i = 0; i < tmp_val; i ++){
                coeficients.push_back(0);
            }
            coeficients.push_back(1);
        }
        else{
            throw "BAN";
        }
    }
    
    std::shared_ptr<TFunction> get_shared() const override{
        return std::make_shared<power>(*this);
    }
};

class exp__ : public TFunction {
    double coefficient;
public:
    exp__();
    exp__(double coef_out);
    exp__(std::initializer_list<double> exp_out);
    double GetDeriv(double point) const override;
    std::string to_string() const override;
    double operator()(double point) const override;
    std::shared_ptr<TFunction> get_shared() const override;
};


class Expression : public TFunction {
protected:
    std::string type_oper;
    std::shared_ptr<TFunction> left;
    std::shared_ptr<TFunction> right;
    
    
public:
    Expression(TFunction& left_out, TFunction& right_out, std::string type_oper_out)
    : left(left_out.get_shared()), right(right_out.get_shared()), type_oper(type_oper_out) {}
//    {
//        left = std::make_shared<Expression>(left_out);
//        right = std::make_shared<Expression>(right_out);
//        type_oper = type_oper_out;
//    }
    double GetDeriv(double point) const override;
    std::string to_string() const override;
    double operator()(double point) const override;
    std::string GetType() const {return type_oper;}
    std::shared_ptr<TFunction> get_shared() const override;
    
};

std::shared_ptr<TFunction> operator + (TFunction& left_out, TFunction& right_out);
std::shared_ptr<TFunction> operator - (TFunction& left_out, TFunction& right_out);
std::shared_ptr<TFunction> operator * (TFunction& left_out, TFunction& right_out);
std::shared_ptr<TFunction> operator / (TFunction& left_out, TFunction& right_out);






#endif /* Function_hpp */
