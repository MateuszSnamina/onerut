#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_opprod.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

// TODO : think
//TEST(operatorOpProd, test0) {
//    using OpT = onerut_normal_operator::AbstractOperator;
//    using OpPtrT = std::shared_ptr<const OpT>;
//    using DomainT = onerut_normal_operator::CustomDomain;
//    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
//    const std::vector<OpPtrT> argv{};
//    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
//    const arma::mat M_expected = arma::eye(4, 4);
//    compare(M_expected, op);
//}

TEST(operatorOpProd, test1) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const std::vector<OpPtrT> argv{op1};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpProd, test2) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const std::vector<OpPtrT> argv{op1};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +3.2, +0.0},
        {+0.0, +3.2, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpProd, test3) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const auto op2 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpProd, test4) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::ZeroOperator>(domain);
    const auto op2 = std::make_shared<onerut_normal_operator::HopOperator>(0.5_R, domain->crate_state(2), domain->crate_state(3));
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M_expected(4, 4, arma::fill::zeros);
    compare(M_expected, op);
}

TEST(operatorOpProd, test5) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const auto op2 = std::make_shared<onerut_normal_operator::HopOperator>(0.5_R, domain->crate_state(2), domain->crate_state(3));
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +1.6},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpProd, test6) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(1), domain->crate_state(0));
    const auto op2 = std::make_shared<onerut_normal_operator::HopOperator>(0.5_R, domain->crate_state(2), domain->crate_state(1));
    const auto op3 = std::make_shared<onerut_normal_operator::HopOperator>(4_I, domain->crate_state(2), domain->crate_state(3));
    const std::vector<OpPtrT> argv{op1, op2, op3};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M_expected = {
        {+0.0, +0.0, +0.0, +6.4},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0},
        {+0.0, +0.0, +0.0, +0.0}
    };
    compare(M_expected, op);
}

TEST(operatorOpProd, test7) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op2 = second_compound_operator(domain);
    const std::vector<OpPtrT> argv{op1, op2};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 * M2;
    compare(M_expected, op);
}

TEST(operatorOpProd, test8) {
    using OpT = onerut_normal_operator::AbstractOperator;
    using OpPtrT = std::shared_ptr<const OpT>;
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op2 = second_compound_operator(domain);
    const std::vector<OpPtrT> argv{op1, op2, op2};
    const auto op = std::make_shared<onerut_normal_operator::OpProdOperator>(argv);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M2 = second_compound_matrix();
    const arma::mat M_expected = M1 * M2 * M2;
    compare(M_expected, op);
}
