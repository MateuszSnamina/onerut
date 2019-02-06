#include<gtest/gtest.h>

#include<onerut_operator_tests/global_flags.hpp>
#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/operator_opplusminus.hpp>
#include<onerut_operator/to_mat.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operator_op_plus_minu, test_1) {

    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;

    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.2, 2, 1);
    auto op2 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(5.5, 1);
    auto op3 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(1.9, 2);
    auto op4 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(7, 0);
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op3, op4});
    std::vector<char> op_opv({'-', '+', '-'});
    auto op = std::make_shared<onerut_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_got = onerut_operator::to_mat(*op, 4);
    const arma::mat M_expected = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            EXPECT_DOUBLE_EQ(M_got(i, j), M_expected(i, j));
}

