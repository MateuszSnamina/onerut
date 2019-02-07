#include<gtest/gtest.h>

#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/operator_scalled.hpp>
#include<onerut_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalled, test_1) {
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(2.6, 2, 1);
    auto op = std::make_shared<onerut_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 9.1, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_scalled, test_2) {
    auto op1 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(2.6, 2);
    auto op = std::make_shared<onerut_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

