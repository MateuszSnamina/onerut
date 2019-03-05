#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_scalled.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorScalled, test1) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});    
    const auto op1 = std::make_shared<onerut_normal_operator::HopOperator>(2.6_R, domain->crate_state(2), domain->crate_state(1));
    const auto op = std::make_shared<onerut_normal_operator::ScalledOperator>(3.5_R, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 9.1, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorScalled, test2) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = std::make_shared<onerut_normal_operator::DiagOperator>(2.6_R, domain->crate_state(2));
    const auto op = std::make_shared<onerut_normal_operator::ScalledOperator>(3.5_R, op1);
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 9.1, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorScalled, test3) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op1 = first_compound_operator(domain);
    const auto op = std::make_shared<onerut_normal_operator::ScalledOperator>(3.5_R, op1);
    const arma::mat M1 = first_compound_matrix();
    const arma::mat M_expected = 3.5 * M1;
    compare(M_expected, op);
}
