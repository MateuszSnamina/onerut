#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_scalled.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------
/*
TEST(operator_scalled, test_1) {
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(2.6, 2, 1);
    const auto op = std::make_shared<onerut_normal_operator::ScalledOperator>(3.5, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 9.1, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_scalled, test_2) {
    const auto op1 = std::make_shared<onerut_normal_operator::DiagOperator>(2.6, 2);
    const auto op = std::make_shared<onerut_normal_operator::ScalledOperator>(3.5, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_scalled, test_3) {
    const auto op1 = first_compound_operator();
    const auto op = std::make_shared<onerut_normal_operator::ScalledOperator>(3.5, op1);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = 3.5 * M1;
    compare(M_expected, op);
}
*/
