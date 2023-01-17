//
//  Factorio.hpp
//  task3
//
//  Created by VolkSeriy on 28.11.2022.
//

#ifndef Factorio_hpp
#define Factorio_hpp

#include <cstdio>
#include <map>

#include "Function.hpp"

class Factorio {
public:
    Factorio()
    {
        RegisterAll();
    }

    class ICreator {
    public:
            virtual std::shared_ptr<TFunction> Create() const = 0;
            virtual std::shared_ptr<TFunction> Create(double param) const = 0;
            virtual std::shared_ptr<TFunction> Create(std::initializer_list<double> params_init) const = 0;
    };

    template <class T>
    class TCreator : public ICreator {
    public:
        std::shared_ptr<TFunction> Create()  const override {
            return std::make_shared<T>(T());
        }

        std::shared_ptr<TFunction> Create(double param) const override {
            return std::make_shared<T>(T(param));
        }
        
        std::shared_ptr<TFunction> Create(std::initializer_list<double> param_init) const override {
            return std::make_shared<T>(T(param_init));
        }
    };

    std::shared_ptr<TFunction> Create(const std::string& factory_type) {
        return RegisteredCreators[factory_type]->Create();
    }

    std::shared_ptr<TFunction> Create(const std::string& factory_type, double param) {
        return RegisteredCreators[factory_type]->Create(param);
    }

    std::shared_ptr<TFunction> Create(const std::string& factory_type, std::initializer_list<double> param_init) {
        return RegisteredCreators[factory_type]->Create(param_init);
    }
private:
    using TCreatorPtr = std::shared_ptr<ICreator>;
    using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
    TRegisteredCreators RegisteredCreators;

    template <typename T>
    void RegisterCreator(const std::string& name) {
        RegisteredCreators[name] = std::make_shared<TCreator<T>>();
    }
    
    std::vector<std::string> GetAvailableObjects () const {
        std::vector<std::string> result;
        for (const auto& creatorPair : RegisteredCreators) {
            result.push_back(creatorPair.first);
        }
        return result;
    }

    void RegisterAll() {
        RegisterCreator<ident>("ident");
        RegisterCreator<const__>("const");
        RegisterCreator<power>("power");
        RegisterCreator<exp__>("exp");
        RegisterCreator<polynomial>("polynomial");
    }

};

double GetGradient(TFunction& left_out, int iteration){
    auto left_out_2 = left_out * left_out;
    auto generator = Factorio();
    auto param = generator.Create("const", {0.001});
    double x_k = 4;
    double x_k_1 = 0;
    for (auto i = 0; i < iteration; i++){
        auto tmp_func = generator.Create("const", {left_out_2->GetDeriv(x_k)});
        x_k_1 = x_k - (*((*param) * (*tmp_func)))(0);
        x_k = x_k_1;
        left_out_2->GetDeriv(0);
    }
    return x_k_1;
}


#endif /* Factorio_hpp */
