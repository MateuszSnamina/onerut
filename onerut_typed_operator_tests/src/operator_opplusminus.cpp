#include<gtest/gtest.h>

#include<onerut_typed_operator/operator_zero.hpp>
#include<onerut_typed_operator/operator_simple.hpp>
#include<onerut_typed_operator/operator_opplusminus.hpp>
#include<onerut_typed_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorOpPlusMinus, test0) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::ZeroOperator<unsigned>>();
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{};
    const std::vector<char> op_opv{};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = arma::mat(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test1) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.2, 2, 1);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{};
    const std::vector<char> op_opv{};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test2) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.2, 2, 1);
    const auto op2 = std::make_shared<onerut_typed_operator::ZeroOperator<unsigned>>();
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2};
    const std::vector<char> op_opv{'+'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test3) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::ZeroOperator<unsigned>>();
    const auto op2 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.2, 2, 1);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2};
    const std::vector<char> op_opv{'+'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test4) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.2, 2, 1);
    const auto op2 = std::make_shared<onerut_typed_operator::DiagOperator<unsigned>>(5.5, 1);
    const auto op3 = std::make_shared<onerut_typed_operator::DiagOperator<unsigned>>(1.9, 2);
    const auto op4 = std::make_shared<onerut_typed_operator::DiagOperator<unsigned>>(7, 0);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2, op3, op4};
    const std::vector<char> op_opv{'-', '+', '-'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test5) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(2.1, 2, 1);
    const auto op2 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(1.1, 2, 3);
    const auto op3 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(1.3, 2, 0);
    const auto op4 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(2.3, 2, 1);
    const auto op5 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.1, 2, 3);
    const auto op6 = std::make_shared<onerut_typed_operator::HopOperator<unsigned>>(3.3, 2, 3);
    const auto op7 = std::make_shared<onerut_typed_operator::DiagOperator<unsigned>>(1.7, 2);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2, op3, op4, op5, op6, op7};
    const std::vector<char> op_opv{'+', '+', '+', '+', '+', '+'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test6) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = first_compound_operator();
    const auto op2 = second_compound_operator();
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2};
    const std::vector<char> op_opv{'-'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 - M2;
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test7) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = first_compound_operator();
    const auto op2 = second_compound_operator();
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2, op1};
    const std::vector<char> op_opv{'-', '+'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 - M2 + M1;
    compare(M_expected, op);
}

TEST(operatorOpPlusMinus, test8) {
    using OpT = onerut_typed_operator::AbstractOperator<unsigned>;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto op1 = std::make_shared<onerut_typed_operator::ZeroOperator<unsigned>>();
    const auto op2 = second_compound_operator();
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op1, op2, op1};
    const std::vector<char> op_opv{'+', '-', '+'};
    const auto op = std::make_shared<onerut_typed_operator::OpPlusMinusOperator<unsigned>>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = -M2;
    compare(M_expected, op);
}