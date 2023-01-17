//
//  main.cpp
//  task3
//
//  Created by VolkSeriy on 27.11.2022.
//

#include <iostream>
#include <cstdio>
//#include "./src/Function.hpp"
#include "./src/Factorio.hpp"

#include <iomanip>

int main(int argc, const char * argv[]) {
    // insert code here...
    auto generator = Factorio();
    auto f = generator.Create("power", 2); // PowerFunc x^2 cont.push_back(f);
    auto g =
    generator.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3 cont.push_back(g);
    auto p = *f / *g;
    
    
    std::cout << p->GetDeriv(3) << std::endl;
    
    return 0;
}
