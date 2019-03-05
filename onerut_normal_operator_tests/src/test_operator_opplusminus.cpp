#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_opplusminus.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(OperatorOpPlusMinus, test0) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{};
    const std::vector<char> op_opv{};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = arma::mat(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test1) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{};
    const std::vector<char> op_opv{};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test2) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const auto op2 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2};
    const std::vector<char> op_opv{'+'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test3) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const auto op2 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2};
    const std::vector<char> op_opv{'+'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test4) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const auto op2 = std::make_shared<onerut_normal_operator::DiagOperator>(5.5_R, domain->crate_state(1));
    const auto op3 = std::make_shared<onerut_normal_operator::DiagOperator>(1.9_R, domain->crate_state(2));
    const auto op4 = std::make_shared<onerut_normal_operator::DiagOperator>(7_I, domain->crate_state(0));
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2, op3, op4};
    const std::vector<char> op_opv{'-', '+', '-'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {-7.0, +0.0, +0.0, +0.0},
        {+0.0, -5.5, +3.2, +0.0},
        {+0.0, +3.2, +1.9, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test5) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(2.1_R, domain->crate_state(2), domain->crate_state(1));
    const auto op2 = std::make_shared<onerut_normal_operator::HopOperator>(1.1_R, domain->crate_state(2), domain->crate_state(3));
    const auto op3 = std::make_shared<onerut_normal_operator::HopOperator>(1.3_R, domain->crate_state(2), domain->crate_state(0));
    const auto op4 = std::make_shared<onerut_normal_operator::HopOperator>(2.3_R, domain->crate_state(2), domain->crate_state(1));
    const auto op5 = std::make_shared<onerut_normal_operator::HopOperator>(3.1_R, domain->crate_state(2), domain->crate_state(3));
    const auto op6 = std::make_shared<onerut_normal_operator::HopOperator>(3.3_R, domain->crate_state(2), domain->crate_state(3));
    const auto op7 = std::make_shared<onerut_normal_operator::DiagOperator>(1.7_R, domain->crate_state(2));
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2, op3, op4, op5, op6, op7};
    const std::vector<char> op_opv{'+', '+', '+', '+', '+', '+'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +1.3, +0.0},
        {+0.0, +0.0, +4.4, +0.0},
        {+1.3, +4.4, +1.7, +7.5},
        {+0.0, +0.0, +7.5, +0.0}
    };
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test6) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op2 = second_compound_operator(domain);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2};
    const std::vector<char> op_opv{'-'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 - M2;
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test7) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op2 = second_compound_operator(domain);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op2, op1};
    const std::vector<char> op_opv{'-', '+'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 - M2 + M1;
    compare(M_expected, op);
}

TEST(OperatorOpPlusMinus, test8) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    const auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const auto op2 = second_compound_operator(domain);
    const OpPtrT op_first_arg = op1;
    const std::vector<OpPtrT> op_other_argv{op1, op2, op1};
    const std::vector<char> op_opv{'+', '-', '+'};
    const auto op = std::make_shared<onerut_normal_operator::OpPlusMinusOperator>(op_first_arg, op_other_argv, op_opv);
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = -M2;
    compare(M_expected, op);
}


