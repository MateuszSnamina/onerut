#include<gtest/gtest.h>

#include<onerut_operator_tests/global_flags.hpp>
#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/operator_scalled.hpp>
#include<onerut_operator/to_mat.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_scalled, test_1) {
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(2.6, 2, 1);
    auto op = std::make_shared<onerut_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M_got = onerut_operator::to_mat(*op, 4);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 9.1, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    if (onerut_verbose) {
        std::cout << "M_got:" << std::endl;
        std::cout << M_got;
        std::cout << "M_expected:" << std::endl;
        std::cout << M_expected;
    }
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            EXPECT_DOUBLE_EQ(M_got(i, j), M_expected(i, j));
}

TEST(operator_scalled, test_2) {
    auto op1 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(2.6, 2);
    auto op = std::make_shared<onerut_operator::ScalledOperator<unsigned>>(3.5, op1);
    const arma::mat M_got = onerut_operator::to_mat(*op, 4);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    if (onerut_verbose) {
        std::cout << "M_got:" << std::endl;
        std::cout << M_got;
        std::cout << "M_expected:" << std::endl;
        std::cout << M_expected;
    }
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            EXPECT_DOUBLE_EQ(M_got(i, j), M_expected(i, j));
}

