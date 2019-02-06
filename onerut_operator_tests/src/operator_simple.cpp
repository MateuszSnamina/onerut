#include<gtest/gtest.h>

#include<onerut_operator_tests/global_flags.hpp>
#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/to_mat.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_diag, test_1) {
    auto op = std::make_shared<onerut_operator::DiagOperator<unsigned>>(7.7, 2);
    const arma::mat M_got = onerut_operator::to_mat(*op, 4);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 7.7, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            EXPECT_DOUBLE_EQ(M_got(i, j), M_expected(i, j));
}

TEST(operator_hop, test_1) {
    auto op = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 2, 1);
    const arma::mat M_got = onerut_operator::to_mat(*op, 4);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 3.2, 0.0},
        {0.0, 3.2, 0.0, 0.0},
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

