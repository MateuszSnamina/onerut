#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalar_integer, test_0) {
    const auto i = std::make_shared<onerut_scalar::LitLong>(6);
    ASSERT_EQ(6.0, i->value_double());
    ASSERT_EQ(6, i->value_long());
}




