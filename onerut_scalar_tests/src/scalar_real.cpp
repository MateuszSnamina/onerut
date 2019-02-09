#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalar_double, test_0) {
    const auto r = std::make_shared<onerut_scalar::LitReal>(-6.7);
    ASSERT_EQ(-6.7, r->value_real());
    ASSERT_EQ(-6.7, r->value_complex());
}

TEST(operator_scalar_double, test_1) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.7);
    const auto r = std::make_shared<onerut_scalar::OpUnaryPlusMinusReal>(r1, '-');
    ASSERT_EQ(-6.7, r->value_real());
    ASSERT_EQ(-6.7, r->value_complex());
}

TEST(operator_scalar_double, test_2) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(7);
    const auto r3 = std::make_shared<onerut_scalar::LitInteger>(5);
    const std::shared_ptr<onerut_scalar::Real> first_arg = r1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        r2, r3
    };
    const std::vector<char> opv{'-', '+'};
    const auto r = std::make_shared<onerut_scalar::OpPlusMinusReal>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, r->value_real());
    ASSERT_EQ(4.0, r->value_complex());
}

TEST(operator_scalar_double, test_3) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(7);
    const auto r3 = std::make_shared<onerut_scalar::LitReal>(5.0);
    const std::shared_ptr<onerut_scalar::Real> first_arg = r1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        r2, r3
    };
    const std::vector<char> opv{'-', '+'};
    const auto r = std::make_shared<onerut_scalar::OpPlusMinusReal>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, r->value_real());
    ASSERT_EQ(4.0, r->value_complex());
}

TEST(operator_scalar_double, test_4) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(-7);
    const auto r3 = std::make_shared<onerut_scalar::LitInteger>(5);
    const std::shared_ptr<onerut_scalar::Real> first_arg = r1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        r2, r3
    };
    const std::vector<char> opv{'*', '/'};
    const auto r = std::make_shared<onerut_scalar::OpProdDivReal>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.0, r->value_real());
    ASSERT_EQ(-8.0, r->value_complex());
}

TEST(operator_scalar_double, test_5) {
    const auto r1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(-7);
    const auto r3 = std::make_shared<onerut_scalar::LitReal>(5.0);
    const std::shared_ptr<onerut_scalar::Real> first_arg = r1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        r2, r3
    };
    const std::vector<char> opv{'*', '/'};
    const auto r = std::make_shared<onerut_scalar::OpProdDivReal>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.4, r->value_real());
    ASSERT_EQ(-8.4, r->value_complex());
}
