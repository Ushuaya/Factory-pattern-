#include <gtest/gtest.h>
#include "../../src/Factorio.hpp"
#include "../../src/Function.hpp"

// compile with:
// g++ -std=c++17 Fuction_test.cpp -o test -lgtest -lgmock -pthread ../../src/Function.cpp ../../src/Factorio.cpp


class Deriv_test : public testing::Test { };

TEST(Deriv_test, Matrix_test_smth1_Test){
    auto generator = Factorio();
    auto f = generator.Create("power", 2); // PowerFunc x^2 cont.push_back(f);
    auto g =
    generator.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3 cont.push_back(g);
    auto p = *f + *g;
    ASSERT_EQ(p->GetDeriv(3), 429);
}

TEST(Deriv_test, Matrix_test_smth2_Test) {
    auto generator = Factorio();
    auto f = generator.Create("power", 2); // PowerFunc x^2 cont.push_back(f);
    auto g =
    generator.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3 cont.push_back(g);
    auto p = *f - *g;
    ASSERT_EQ(p->GetDeriv(3), -417);
}

TEST(Deriv_test, Matrix_test_smth3_Test) {
    auto generator = Factorio();
    auto f = generator.Create("power", 2); // PowerFunc x^2 cont.push_back(f);
    auto g =
    generator.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3 cont.push_back(g);
    auto p = *f * *g;
    ASSERT_EQ(p->GetDeriv(3), 6441);
}

TEST(Deriv_test, Matrix_test_smth4_Test) {
    auto generator = Factorio();
    auto f = generator.Create("power", 2); // PowerFunc x^2 cont.push_back(f);
    auto g =
    generator.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3 cont.push_back(g);
    auto p = *f / *g;
    EXPECT_NEAR(p->GetDeriv(3), -0.296887, 0.003);
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


