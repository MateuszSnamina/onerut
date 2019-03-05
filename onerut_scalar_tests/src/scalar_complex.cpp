#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

using namespace std::complex_literals;

TEST(operatorScalarComplex, test0) {
    const auto d = std::make_shared<onerut_scalar::LitComplex>(-6.7 + 2.5i);
    ASSERT_EQ(-6.7 + 2.5i, d->value_complex());
}

TEST(operatorScalarComplex, test1) {
    const auto r1 = std::make_shared<onerut_scalar::LitComplex>(6.7 + 2.5i);
    const auto r = std::make_shared<onerut_scalar::OpUnaryPlusMinusComplex>(r1, '-');
    ASSERT_EQ(-6.7 - 2.5i, r->value_complex());
}

TEST(operatorScalarComplex, test2) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(7);
    const auto r3 = std::make_shared<onerut_scalar::LitInteger>(5);
    const std::shared_ptr<onerut_scalar::Complex> first_arg = r1;
    const std::vector<std::shared_ptr <const onerut_scalar::Complex >> other_argv
    {
        r2, r3
    };
    const std::vector<char> opv{'-', '+'};
    const auto r = std::make_shared<onerut_scalar::OpPlusMinusComplex>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, r->value_complex());
}

TEST(operatorScalarComplex, test3) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(7);
    const auto r3 = std::make_shared<onerut_scalar::LitReal>(5.0);
    const std::shared_ptr<onerut_scalar::Complex> first_arg = r1;
    const std::vector<std::shared_ptr <const onerut_scalar::Complex > > other_argv{r2, r3};
    const std::vector<char> opv{'-', '+'};
    const auto r = std::make_shared<onerut_scalar::OpPlusMinusComplex>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, r->value_complex());
}

TEST(operatorScalarComplex, test4) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitComplex>(7.4 + 5.2i);
    const auto r3 = std::make_shared<onerut_scalar::LitComplex>(5.5 - 5.7i);
    const std::shared_ptr<onerut_scalar::Complex> first_arg = r1;
    const std::vector<std::shared_ptr <const onerut_scalar::Complex > > other_argv{r2, r3};
    const std::vector<char> opv{'-', '+'};
    const auto r = std::make_shared<onerut_scalar::OpPlusMinusComplex>(first_arg, other_argv, opv);
    ASSERT_EQ(double(6) - (7.4 + 5.2i) + (5.5 - 5.7i), r->value_complex());
}

TEST(operatorScalarComplex, test5) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(-7);
    const auto r3 = std::make_shared<onerut_scalar::LitInteger>(5);
    const std::shared_ptr<onerut_scalar::Complex> first_arg = r1;
    const std::vector<std::shared_ptr <const onerut_scalar::Complex > > other_argv{r2, r3};
    const std::vector<char> opv{'*', '/'};
    const auto r = std::make_shared<onerut_scalar::OpProdDivComplex>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.0, r->value_complex());
}

TEST(operatorScalarComplex, test6) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(-7);
    const auto r3 = std::make_shared<onerut_scalar::LitReal>(5.0);
    const std::shared_ptr<onerut_scalar::Complex> first_arg = r1;
    const std::vector<std::shared_ptr <const onerut_scalar::Complex > > other_argv{r2, r3};
    const std::vector<char> opv{'*', '/'};
    const auto r = std::make_shared<onerut_scalar::OpProdDivComplex>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.4, r->value_complex());
}

TEST(operatorScalarComplex, test7) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitComplex>(7.4 + 5.2i);
    const auto r3 = std::make_shared<onerut_scalar::LitComplex>(5.5 - 5.7i);
    const std::shared_ptr<onerut_scalar::Complex> first_arg = r1;
    const std::vector<std::shared_ptr <const onerut_scalar::Complex > > other_argv{r2, r3};
    const std::vector<char> opv{'/', '*'};
    const auto r = std::make_shared<onerut_scalar::OpProdDivComplex>(first_arg, other_argv, opv);
    ASSERT_EQ(double(6) / (7.4 + 5.2i) * (5.5 - 5.7i), r->value_complex());
}