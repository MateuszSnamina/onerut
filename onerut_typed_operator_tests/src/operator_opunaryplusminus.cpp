#include<gtest/gtest.h>

#include<onerut_typed_operator/operator_simple.hpp>
#include<onerut_typed_operator/operator_opunaryplusminus.hpp>
#include<onerut_typed_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorOpUnaryPlusMinus, test1) {
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<double, unsigned>>(2.6, 2, 1);
    const auto op = std::make_shared<onerut_typed_operator::OpUnaryPlusMinusOperator<double, unsigned>>(op1, '+');
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 2.6, 0.0},
        {0.0, 2.6, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpUnaryPlusMinus, test2) {
    const auto op1 = std::make_shared<onerut_typed_operator::DiagOperator<double, unsigned>>(2.6, 2);
    const auto op = std::make_shared<onerut_typed_operator::OpUnaryPlusMinusOperator<double, unsigned>>(op1, '-');
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, -2.6, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpUnaryPlusMinus, test3) {
    const auto op1 = first_compound_operator();
    const auto op = std::make_shared<onerut_typed_operator::OpUnaryPlusMinusOperator<double, unsigned>>(op1, '+');
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = +M1;
    compare(M_expected, op);
}

TEST(operatorOpUnaryPlusMinus, test4) {
    const auto op1 = first_compound_operator();
    const auto op = std::make_shared<onerut_typed_operator::OpUnaryPlusMinusOperator<double, unsigned>>(op1, '-');
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = -M1;
    compare(M_expected, op);
}