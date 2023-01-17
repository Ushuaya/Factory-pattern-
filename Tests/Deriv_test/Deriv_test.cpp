#include <gtest/gtest.h>
#include "../../src/Factorio.hpp"
#include "../../src/Function.hpp"

// compile with:
// g++ -std=c++17 Fuction_test.cpp -o test -lgtest -lgmock -pthread ../../src/Function.cpp ../../src/Factorio.cpp


class Deriv_test : public testing::Test { };

TEST(Deriv_test, Matrix_test_smth1_Test){
    auto generator = Factorio();
    auto f = generator.Create("power", 2); // PowerFunc x^2 cont.push_back(f);
    ASSERT_EQ(f->GetDeriv(3), 6);
}

TEST(Deriv_test, Matrix_test_smth2_Test) {
    auto generator = Factorio();
    auto f = generator.Create("polynomial", {1, 2, 3}); // PowerFunc x^2 cont.push_back(f);
    ASSERT_EQ(f->GetDeriv(3), 20);
}

TEST(Deriv_test, Matrix_test_smth3_Test) {
    auto generator = Factorio();
    auto f = generator.Create("ident", {5}); // PowerFunc x^2 cont.push_back(f);
    ASSERT_EQ(f->GetDeriv(3), 5);
}

TEST(Deriv_test, Matrix_test_smth4_Test) {
    auto generator = Factorio();
    auto f = generator.Create("const", {1}); // PowerFunc x^2 cont.push_back(f);
    ASSERT_EQ(f->GetDeriv(3), 0);
}

TEST(Deriv_test, Matrix_test_smth5_Test) {
    auto generator = Factorio();
    auto f = generator.Create("exp", {0}); // PowerFunc x^2 cont.push_back(f);
    ASSERT_EQ(f->GetDeriv(3), 0);
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

