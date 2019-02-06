#include<gtest/gtest.h>

#include<onerut_operator_tests/global_flags.hpp>
#include<onerut_operator/operator_opprod.hpp>
#include<onerut_operator/to_mat.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_op_prod, test_1) {
    
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    //using OpPtrT = std::shared_ptr<const OpT>;
/*    
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
 */
}

