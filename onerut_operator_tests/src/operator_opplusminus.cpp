#include<gtest/gtest.h>

#include<onerut_operator/operator_simple.hpp>
#include<onerut_operator/operator_opplusminus.hpp>
#include<onerut_operator_tests/common.hpp>

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
    const arma::mat M_expected = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operator_op_plus_minu, test_2) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    auto op1 = std::make_shared<onerut_operator::HopOperator<unsigned>>(2.1, 2, 1);
    auto op2 = std::make_shared<onerut_operator::HopOperator<unsigned>>(1.1, 2, 3);
    auto op3 = std::make_shared<onerut_operator::HopOperator<unsigned>>(1.3, 2, 0);
    auto op4 = std::make_shared<onerut_operator::HopOperator<unsigned>>(2.3, 2, 1);
    auto op5 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.1, 2, 3);
    auto op6 = std::make_shared<onerut_operator::HopOperator<unsigned>>(3.3, 2, 3);
    auto op7 = std::make_shared<onerut_operator::DiagOperator<unsigned>>(1.7, 2);
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op3, op4, op5, op6, op7});
    std::vector<char> op_opv({'+', '+', '+', '+', '+', '+'});
    auto op = std::make_shared<onerut_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    compare(M_expected, op);
}

TEST(operator_op_plus_minu, test_3) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op2 = second_compound_operator();
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2});
    std::vector<char> op_opv({'-'});
    auto op = std::make_shared<onerut_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M1 = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    const arma::mat M2 = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    const arma::mat M_expected = M1 - M2;
    compare(M_expected, op);
}

TEST(operator_op_plus_minu, test_4) {
    using OpT = onerut_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op1 = first_compound_operator();
    std::shared_ptr<onerut_operator::AbstractOperator<unsigned>> op2 = second_compound_operator();
    OpPtrT op_first_arg = op1;
    std::vector<OpPtrT> op_other_argv({op2, op1});
    std::vector<char> op_opv({'-', '+'});
    auto op = std::make_shared<onerut_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M1 = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    const arma::mat M2 = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    const arma::mat M_expected = M1 - M2 + M1;
    compare(M_expected, op);
}