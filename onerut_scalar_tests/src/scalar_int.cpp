#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalar_integer, test_0) {
    const auto i = std::make_shared<onerut_scalar::LitLong>(-6);
    ASSERT_EQ(-6.0, i->value_double());
    ASSERT_EQ(-6, i->value_long());
}

TEST(operator_scalar_integer, test_1) {
    const auto i1 = std::make_shared<onerut_scalar::LitLong>(6);
    const auto i = std::make_shared<onerut_scalar::OpUnaryPlusMinusLong>(i1, '-');
    ASSERT_EQ(-6.0, i->value_double());
    ASSERT_EQ(-6, i->value_long());
}

TEST(operator_scalar_integer, test_2) {
    const auto i1 = std::make_shared<onerut_scalar::LitLong>(6);
    const auto i2 = std::make_shared<onerut_scalar::LitLong>(7);
    const auto i3 = std::make_shared<onerut_scalar::LitLong>(5);
    const std::shared_ptr<onerut_scalar::Long> first_arg = i1;
    const std::vector<std::shared_ptr < onerut_scalar::Long >> other_argv{i2, i3};
    const std::vector<char> opv{'-', '+'};
    const auto i = std::make_shared<onerut_scalar::OpPlusMinusLong>(first_arg, other_argv, opv);
    ASSERT_EQ(4.0, i->value_double());
    ASSERT_EQ(4, i->value_long());
}

TEST(operator_scalar_integer, test_3) {
    const auto i1 = std::make_shared<onerut_scalar::LitLong>(6);
    const auto i2 = std::make_shared<onerut_scalar::LitLong>(-7);
    const auto i3 = std::make_shared<onerut_scalar::LitLong>(5);
    const std::shared_ptr<onerut_scalar::Long> first_arg = i1;
    const std::vector<std::shared_ptr < onerut_scalar::Long >> other_argv{i2, i3};
    const std::vector<char> opv{'*', '/'};
    const auto i = std::make_shared<onerut_scalar::OpProdDivLong>(first_arg, other_argv, opv);
    ASSERT_EQ(-8.0, i->value_double());
    ASSERT_EQ(-8, i->value_long());
}






