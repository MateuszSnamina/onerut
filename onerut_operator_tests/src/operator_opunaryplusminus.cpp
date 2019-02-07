#include<gtest/gtest.h>

#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/operator_opunaryplusminus.hpp>
#include<onerut_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_opunaryplusminus, test_1) {
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(2.6, 2, 1);
    auto op = std::make_shared<onerut_operator::OpUnaryPlusMinusOperator<unsigned>>('+', op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 2.6, 0.0},
        {0.0, 2.6, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_opunaryplusminus, test_2) {
    auto op1 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(2.6, 2);
    auto op = std::make_shared<onerut_operator::OpUnaryPlusMinusOperator<unsigned>>('-', op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, -2.6, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operator_opunaryplusminus, test_3) {
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    auto op = std::make_shared<onerut_operator::OpUnaryPlusMinusOperator<unsigned>>('+', op1);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = +M1;
    compare(M_expected, op);
}

TEST(operator_opunaryplusminus, test_4) {
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    auto op = std::make_shared<onerut_operator::OpUnaryPlusMinusOperator<unsigned>>('-', op1);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = -M1;
    compare(M_expected, op);
}
