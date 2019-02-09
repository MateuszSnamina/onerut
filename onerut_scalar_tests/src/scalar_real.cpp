#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalar_double, test_0) {
    const auto d = std::make_shared<onerut_scalar::LitReal>(-6.7);
    ASSERT_EQ(-6.7, d->value_real());
}

TEST(operator_scalar_double, test_1) {
    const auto i1 = std::make_shared<onerut_scalar::LitReal>(6.7);
    const auto i = std::make_shared<onerut_scalar::OpUnaryPlusMinusReal>(i1, '-');
    ASSERT_EQ(-6.7, i->value_real());
}

TEST(operator_scalar_double, test_2) {
    const auto i1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto i2 = std::make_shared<onerut_scalar::LitInteger>(7);
    const auto i3 = std::make_shared<onerut_scalar::LitInteger>(5);
    const std::shared_ptr<onerut_scalar::Real> first_arg = i1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        i2, i3
    };
    const std::vector<char> opv{'-', '+'};
    const auto i = std::make_shared<onerut_scalar::OpPlusMinusReal>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, i->value_real());
}

TEST(operator_scalar_double, test_3) {
    const auto i1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto i2 = std::make_shared<onerut_scalar::LitInteger>(7);
    const auto i3 = std::make_shared<onerut_scalar::LitReal>(5.0);
    const std::shared_ptr<onerut_scalar::Real> first_arg = i1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        i2, i3
    };
    const std::vector<char> opv{'-', '+'};
    const auto i = std::make_shared<onerut_scalar::OpPlusMinusReal>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, i->value_real());
}

TEST(operator_scalar_double, test_4) {
    const auto i1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto i2 = std::make_shared<onerut_scalar::LitInteger>(-7);
    const auto i3 = std::make_shared<onerut_scalar::LitInteger>(5);
    const std::shared_ptr<onerut_scalar::Real> first_arg = i1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        i2, i3
    };
    const std::vector<char> opv{'*', '/'};
    const auto i = std::make_shared<onerut_scalar::OpProdDivReal>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.0, i->value_real());
}

TEST(operator_scalar_double, test_5) {
    const auto i1 = std::make_shared<onerut_scalar::LitInteger>(6);
    const auto i2 = std::make_shared<onerut_scalar::LitInteger>(-7);
    const auto i3 = std::make_shared<onerut_scalar::LitReal>(5.0);
    const std::shared_ptr<onerut_scalar::Real> first_arg = i1;
    const std::vector<std::shared_ptr < onerut_scalar::Real >> other_argv
    {
        i2, i3
    };
    const std::vector<char> opv{'*', '/'};
    const auto i = std::make_shared<onerut_scalar::OpProdDivReal>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.4, i->value_real());
}
