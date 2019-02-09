#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalar_double, test_0) {
    const auto d = std::make_shared<onerut_scalar::LitDouble>(6.7);
    ASSERT_EQ(6.7, d->value_double());
    //ASSERT_EQ(6, d->value_long());
}

