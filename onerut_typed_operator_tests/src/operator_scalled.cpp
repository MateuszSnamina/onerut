#include<gtest/gtest.h>

#include<onerut_typed_operator/operator_simple.hpp>
#include<onerut_typed_operator/operator_scalled.hpp>
#include<onerut_typed_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorScalled, test1) {
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(2.6, 2, 1);
    const auto op = std::make_shared<onerut_typed_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 9.1, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorScalled, test2) {
    const auto op1 = std::make_shared<onerut_typed_operator::DiagOperator<unsigned>>(2.6, 2);
    const auto op = std::make_shared<onerut_typed_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorScalled, test3) {
    const auto op1 = first_compound_operator();
    const auto op = std::make_shared<onerut_typed_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = 3.5 * M1;
    compare(M_expected, op);
}