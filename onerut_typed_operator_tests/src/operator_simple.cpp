#include<gtest/gtest.h>

#include<onerut_typed_operator/operator_simple.hpp>
#include<onerut_typed_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorDiag, test1) {
    const auto op = std::make_shared<onerut_typed_operator::DiagOperator<unsigned>>(7.7, 2);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 7.7, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorHop, test1) {
    const auto op = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.2, 2, 1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 3.2, 0.0},
        {0.0, 3.2, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}