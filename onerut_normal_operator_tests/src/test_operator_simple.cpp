#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator_tests/common.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(operatorDiag, test1) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op = std::make_shared<onerut_normal_operator::DiagOperator>(7.7_R, domain->crate_state(2));
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 7.7, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorHop, test1) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op = std::make_shared<onerut_normal_operator::HopOperator>(3.2_R, domain->crate_state(2), domain->crate_state(1));
    const arma::mat M_expected = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 3.2, 0.0},
        {0.0, 3.2, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    compare(M_expected, op);
}

TEST(operatorEye, test1) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto op = std::make_shared<onerut_normal_operator::EyeOperator>(domain);
    const arma::mat M_expected = arma::eye(4,4);
    compare(M_expected, op);
}

